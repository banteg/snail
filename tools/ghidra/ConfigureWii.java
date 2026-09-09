import ghidra.app.script.GhidraScript;

// Explicitly enable the extension analyzer: its default format-name check
// does not match every DOL loader version's "(Executable)" suffix.
public class ConfigureWii extends GhidraScript {
    @Override
    public void run() throws Exception {
        if (!currentProgram.getLanguageID().toString().equals("PowerPC:BE:32:Gekko_Broadway")) {
            throw new IllegalStateException("Wii import requires the Gekko/Broadway language");
        }
        setAnalysisOption(currentProgram, "(GameCube/Wii) Program Analyzer", "true");
    }
}
