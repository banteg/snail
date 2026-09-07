import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import java.nio.file.Files;
import java.nio.file.Path;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.HexFormat;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

// Read-only snapshot. Arguments: PE section specification JSON, output JSON.
public class ExportCodeInventory extends GhidraScript {
    static class Section {
        String name;
        long start;
        long end;
        String sha256;
        List<List<Object>> classification = new ArrayList<>();
    }

    static class Specification {
        String input_sha256;
        List<Section> sections;
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        Specification spec = new Gson().fromJson(Files.readString(Path.of(args[0])), Specification.class);
        if (!spec.input_sha256.equalsIgnoreCase(currentProgram.getExecutableSHA256())) {
            throw new IllegalStateException("Ghidra input hash does not match original PE");
        }
        var listing = currentProgram.getListing();
        for (Section section : spec.sections) {
            int size = Math.toIntExact(section.end - section.start);
            byte[] bytes = new byte[size];
            int read = currentProgram.getMemory().getBytes(toAddr(section.start), bytes);
            String hash = HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(bytes));
            if (read != size || !hash.equals(section.sha256)) {
                throw new IllegalStateException("Ghidra section bytes differ from original PE");
            }
            section.classification = new ArrayList<>();
            long runStart = section.start;
            String previous = null;
            for (long address = section.start; address < section.end; address++) {
                monitor.checkCancelled();
                Instruction instruction = listing.getInstructionContaining(toAddr(address));
                Data data = listing.getDefinedDataContaining(toAddr(address));
                String kind = instruction != null ? "code"
                    : data != null && data.isDefined() ? "data" : "unknown";
                if (!kind.equals(previous)) {
                    if (previous != null) {
                        section.classification.add(List.of(runStart, address, previous));
                    }
                    previous = kind;
                    runStart = address;
                }
            }
            section.classification.add(List.of(runStart, section.end, previous));
        }
        List<Map<String, Object>> functions = new ArrayList<>();
        for (Function function : currentProgram.getFunctionManager().getFunctions(true)) {
            long start = function.getEntryPoint().getOffset();
            if (spec.sections.stream().noneMatch(s -> s.start <= start && start < s.end)) continue;
            List<List<Long>> ranges = new ArrayList<>();
            for (AddressRange range : function.getBody().getAddressRanges()) {
                ranges.add(List.of(range.getMinAddress().getOffset(), range.getMaxAddress().getOffset() + 1));
            }
            Map<String, Object> row = new LinkedHashMap<>();
            row.put("start", start);
            row.put("name", function.getName());
            row.put("ranges", ranges);
            functions.add(row);
        }
        Map<String, Object> output = new LinkedHashMap<>();
        output.put("schema_version", 1);
        output.put("tool", "Ghidra");
        output.put("tool_version", Application.getApplicationVersion());
        output.put("input_sha256", spec.input_sha256);
        output.put("sections", spec.sections);
        output.put("functions", functions);
        Files.writeString(Path.of(args[1]), new GsonBuilder().setPrettyPrinting().create().toJson(output) + "\n");
    }
}
