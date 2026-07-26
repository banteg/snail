import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class DecompileSymbol extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) {
            throw new IllegalArgumentException(
                "expected a function-name fragment and output path");
        }
        Path outputPath = Path.of(args[1]);

        Function selected = null;
        String selector = args[0];
        if (selector.matches("0[xX][0-9a-fA-F]+")) {
            Address address =
                currentProgram.getAddressFactory().getAddress(selector);
            if (address == null) {
                throw new IllegalStateException(
                    "invalid function address: " + selector);
            }
            selected =
                currentProgram.getFunctionManager().getFunctionAt(address);
            if (selected == null) {
                throw new IllegalStateException(
                    "no function at " + selector);
            }
        } else {
            for (Function function :
                    currentProgram.getFunctionManager().getFunctions(true)) {
                String name = function.getName(true);
                if (!name.contains(selector)) {
                    continue;
                }
                if (selected != null) {
                    throw new IllegalStateException(
                        "ambiguous function fragment: " + selector);
                }
                selected = function;
            }
            if (selected == null) {
                throw new IllegalStateException(
                    "no function matching " + selector);
            }
        }

        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.toggleSyntaxTree(true);
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException(decompiler.getLastMessage());
        }

        DecompileResults result =
            decompiler.decompileFunction(selected, 60, monitor);
        if (!result.decompileCompleted()) {
            throw new IllegalStateException(result.getErrorMessage());
        }

        String output =
            "GHIDRA_VERSION=" + Application.getApplicationVersion() + "\n"
            + "FUNCTION=" + selected.getName(true) + "@"
            + selected.getEntryPoint() + "\n"
            + result.getDecompiledFunction().getC() + "\n";
        Files.writeString(outputPath, output, StandardCharsets.UTF_8);
    }
}
