import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.listing.Function;

public class DecompileSymbol extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) {
            throw new IllegalArgumentException(
                "expected one function-name fragment");
        }

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

        println("GHIDRA_VERSION=" + Application.getApplicationVersion());
        println("FUNCTION=" + selected.getName(true) + "@"
            + selected.getEntryPoint());
        println(result.getDecompiledFunction().getC());
    }
}
