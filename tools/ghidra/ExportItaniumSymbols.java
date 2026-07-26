import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Parameter;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolTable;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

public class ExportItaniumSymbols extends GhidraScript {
    private static class RequestedSymbol {
        String mangled;
        String binarySymbol;
        String demangled;
    }

    private static class ExportedFunction {
        String mangled;
        String binary_symbol;
        String demangled;
        String address;
        long size;
        List<String> params = new ArrayList<>();
        String prototype;
        String path;
        String status;
        String error;
    }

    private static class ExportIndex {
        String ghidra_version;
        String program;
        String executable_sha256;
        int symbol_count;
        int exported_count;
        int failed_count;
        List<ExportedFunction> functions = new ArrayList<>();
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 3) {
            throw new IllegalArgumentException(
                "expected a symbol manifest, output directory, and timeout");
        }

        Path manifestPath = Path.of(args[0]);
        Path outputRoot = Path.of(args[1]);
        int timeoutSeconds = Integer.parseInt(args[2]);
        if (timeoutSeconds < 1) {
            throw new IllegalArgumentException("timeout must be positive");
        }

        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        RequestedSymbol[] requested = gson.fromJson(
            Files.readString(manifestPath, StandardCharsets.UTF_8),
            RequestedSymbol[].class);
        Path functionsRoot = outputRoot.resolve("functions");
        Files.createDirectories(functionsRoot);

        ExportIndex index = new ExportIndex();
        index.ghidra_version = Application.getApplicationVersion();
        index.program = currentProgram.getName();
        index.executable_sha256 = currentProgram.getExecutableSHA256();
        index.symbol_count = requested.length;

        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.toggleSyntaxTree(true);
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException(decompiler.getLastMessage());
        }

        for (RequestedSymbol request : requested) {
            monitor.checkCancelled();
            ExportedFunction exported = exportOne(
                request, functionsRoot, decompiler, timeoutSeconds);
            index.functions.add(exported);
            if ("ok".equals(exported.status)) {
                index.exported_count++;
            } else {
                index.failed_count++;
            }
        }

        Files.writeString(
            outputRoot.resolve("index.json"),
            gson.toJson(index) + "\n",
            StandardCharsets.UTF_8);
    }

    private ExportedFunction exportOne(
            RequestedSymbol request,
            Path functionsRoot,
            DecompInterface decompiler,
            int timeoutSeconds) {
        ExportedFunction exported = new ExportedFunction();
        exported.mangled = request.mangled;
        exported.binary_symbol = request.binarySymbol;
        exported.demangled = request.demangled;

        try {
            Function function = resolveFunction(request);
            if (function == null) {
                throw new IllegalStateException(
                    "no Ghidra function for symbol " + request.binarySymbol);
            }

            exported.address = function.getEntryPoint().toString();
            exported.size = function.getBody().getNumAddresses();
            exported.prototype = function.getPrototypeString(
                true, true);
            for (Parameter parameter : function.getParameters()) {
                exported.params.add(
                    parameter.getDataType().getDisplayName());
            }

            DecompileResults result = decompiler.decompileFunction(
                function, timeoutSeconds, monitor);
            if (!result.decompileCompleted()) {
                throw new IllegalStateException(result.getErrorMessage());
            }

            String filename = makeFilename(
                exported.address, request.mangled);
            exported.path = "functions/" + filename;
            String output =
                "/*\n"
                + " * mangled: " + request.mangled + "\n"
                + " * demangled: " + request.demangled + "\n"
                + " * address: " + exported.address + "\n"
                + " * size: " + exported.size + "\n"
                + " */\n"
                + result.getDecompiledFunction().getC()
                + "\n";
            Files.writeString(
                functionsRoot.resolve(filename),
                output,
                StandardCharsets.UTF_8);
            exported.status = "ok";
        } catch (Exception error) {
            exported.status = "error";
            exported.error = error.getMessage();
            if (exported.error == null || exported.error.isBlank()) {
                exported.error = error.getClass().getName();
            }
        }
        return exported;
    }

    private Function resolveFunction(RequestedSymbol request) {
        SymbolTable symbolTable = currentProgram.getSymbolTable();
        Set<String> candidateNames = new LinkedHashSet<>();
        candidateNames.add(request.binarySymbol);
        candidateNames.add(request.mangled);
        if (request.binarySymbol.startsWith("__ZN")) {
            candidateNames.add(request.binarySymbol.substring(1));
        }

        for (String name : candidateNames) {
            SymbolIterator symbols = symbolTable.getSymbols(name);
            for (Symbol symbol : symbols) {
                Function function = functionForSymbol(symbol);
                if (function != null) {
                    return function;
                }
            }
        }

        String qualifiedName = qualifiedName(request.demangled);
        int parameterCount = parameterCount(request.demangled);
        Function selected = null;
        for (Function function :
                currentProgram.getFunctionManager().getFunctions(true)) {
            if (!function.getName(true).equals(qualifiedName)) {
                continue;
            }
            if (parameterCount >= 0
                    && function.getParameterCount() != parameterCount) {
                continue;
            }
            if (selected != null
                    && !selected.getEntryPoint().equals(
                        function.getEntryPoint())) {
                return null;
            }
            selected = function;
        }
        return selected;
    }

    private Function functionForSymbol(Symbol symbol) {
        Object object = symbol.getObject();
        if (object instanceof Function) {
            return (Function) object;
        }
        Function function = currentProgram.getFunctionManager().getFunctionAt(
            symbol.getAddress());
        if (function != null) {
            return function;
        }
        return currentProgram.getFunctionManager().getFunctionContaining(
            symbol.getAddress());
    }

    private String qualifiedName(String demangled) {
        int open = demangled.indexOf('(');
        return open < 0 ? demangled : demangled.substring(0, open);
    }

    private int parameterCount(String demangled) {
        int open = demangled.indexOf('(');
        int close = demangled.lastIndexOf(')');
        if (open < 0 || close < open) {
            return -1;
        }
        String parameters = demangled.substring(open + 1, close).trim();
        if (parameters.isEmpty() || "void".equals(parameters)) {
            return 0;
        }
        int count = 1;
        int depth = 0;
        for (int index = 0; index < parameters.length(); index++) {
            char current = parameters.charAt(index);
            if (current == '<' || current == '(' || current == '[') {
                depth++;
            } else if (
                    current == '>' || current == ')' || current == ']') {
                depth--;
            } else if (current == ',' && depth == 0) {
                count++;
            }
        }
        return count;
    }

    private String makeFilename(String address, String mangled)
            throws Exception {
        String safeAddress = address.replaceAll(
            "[^A-Za-z0-9_.-]", "_");
        String safeMangled = mangled.replaceAll(
            "[^A-Za-z0-9_.-]", "_");
        if (safeMangled.length() > 160) {
            safeMangled = safeMangled.substring(0, 140)
                + "-"
                + shortHash(mangled);
        }
        return safeAddress + "-" + safeMangled + ".c";
    }

    private String shortHash(String value) throws Exception {
        byte[] digest = MessageDigest.getInstance("SHA-256").digest(
            value.getBytes(StandardCharsets.UTF_8));
        StringBuilder output = new StringBuilder();
        for (int index = 0; index < 6; index++) {
            output.append(String.format("%02x", digest[index]));
        }
        return output.toString();
    }
}
