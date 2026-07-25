import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
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
        for (Function function :
                currentProgram.getFunctionManager().getFunctions(true)) {
            String name = function.getName(true);
            if (!name.contains(args[0])) {
                continue;
            }
            if (selected != null) {
                throw new IllegalStateException(
                    "ambiguous function fragment: " + args[0]);
            }
            selected = function;
        }
        if (selected == null) {
            throw new IllegalStateException(
                "no function matching " + args[0]);
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
