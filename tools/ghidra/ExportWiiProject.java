import com.google.gson.GsonBuilder;
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.*;
import java.security.MessageDigest;
import java.util.*;

// Verify original DOL mappings and persist the one cross-port identity already
// established by the committed PowerPC/Windows instruction evidence.
public class ExportWiiProject extends GhidraScript {
    private String hash(byte[] bytes) throws Exception {
        return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(bytes));
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        byte[] dol = Files.readAllBytes(Path.of(args[0]));
        ByteBuffer header = ByteBuffer.wrap(dol).order(ByteOrder.BIG_ENDIAN);
        String language = currentProgram.getLanguageID().toString();
        if (!language.equals("PowerPC:BE:32:Gekko_Broadway") ||
            !hash(dol).equalsIgnoreCase(currentProgram.getExecutableSHA256())) {
            throw new IllegalStateException("Wii language or imported DOL hash differs");
        }
        List<Map<String, Object>> sections = new ArrayList<>();
        for (int kind = 0; kind < 2; kind++) {
            int count = kind == 0 ? 7 : 11;
            int offBase = kind == 0 ? 0 : 0x1c;
            int addrBase = kind == 0 ? 0x48 : 0x64;
            int sizeBase = kind == 0 ? 0x90 : 0xac;
            for (int i = 0; i < count; i++) {
                int size = header.getInt(sizeBase + i * 4);
                if (size == 0) continue;
                int offset = header.getInt(offBase + i * 4);
                long address = Integer.toUnsignedLong(header.getInt(addrBase + i * 4));
                byte[] original = Arrays.copyOfRange(dol, offset, offset + size);
                byte[] loaded = new byte[size];
                int read = currentProgram.getMemory().getBytes(toAddr(address), loaded);
                if (read != size || !Arrays.equals(original, loaded)) {
                    throw new IllegalStateException("DOL section mismatch at " + Long.toHexString(address));
                }
                sections.add(Map.of("name", (kind == 0 ? "text" : "data") + i,
                    "address", Long.toHexString(address), "size", size, "sha256", hash(loaded)));
            }
        }
        Map<String, Object> registers = new LinkedHashMap<>();
        for (String name : List.of("r2", "r13", "GQR0", "GQR1", "GQR2", "GQR3", "GQR4", "GQR5", "GQR6", "GQR7")) {
            var register = currentProgram.getRegister(name);
            var value = currentProgram.getProgramContext().getValue(register, toAddr("8000a968"), false);
            registers.put(name, value == null ? "unknown" : value.toString(16));
        }
        if (!registers.get("r2").equals("808fc860") || !registers.get("r13").equals("808fb720")) {
            throw new IllegalStateException("SDA register analysis differs from entry initialization: " + registers);
        }
        Function quaternion = getFunctionAt(toAddr("8000a968"));
        if (quaternion == null) throw new IllegalStateException("Quaternion function was not discovered");
        if (quaternion.getSymbol().getSource() == SourceType.DEFAULT) {
            quaternion.setName("initialize_quaternion_from_matrix", SourceType.USER_DEFINED);
            quaternion.setComment("Recovered cross-port identity: tQuaternian::tQuaternian(const tMatrix&). " +
                "Windows 0x44d5d0; see tools/match/quaternion-wii-dispatch-20260909.md. " +
                "This is an analyst name, not an original Wii symbol.");
        }
        if (quaternion.getBody().getNumAddresses() != 768) {
            throw new IllegalStateException("Quaternion extent differs from committed evidence");
        }
        List<Map<String, Object>> functions = new ArrayList<>();
        for (Function function : currentProgram.getFunctionManager().getFunctions(true)) {
            functions.add(Map.of("address", function.getEntryPoint().toString(),
                "name", function.getName(true), "bytes", function.getBody().getNumAddresses()));
        }
        int paired = 0;
        List<String> pairedExamples = new ArrayList<>();
        for (Instruction instruction : currentProgram.getListing().getInstructions(true)) {
            if (instruction.getMnemonicString().startsWith("ps")) {
                paired++;
                if (pairedExamples.size() < 8) pairedExamples.add(instruction.getAddress() + ": " + instruction);
            }
        }
        if (paired == 0) throw new IllegalStateException("No paired-single instructions decoded");
        Map<String, Object> result = new LinkedHashMap<>();
        result.put("ghidra_version", Application.getApplicationVersion());
        result.put("program", currentProgram.getName());
        result.put("input_sha256", hash(dol));
        result.put("language", language);
        result.put("format", currentProgram.getExecutableFormat());
        result.put("sections", sections);
        result.put("registers_at_quaternion", registers);
        result.put("function_count", functions.size());
        result.put("functions", functions);
        result.put("paired_single_instructions", paired);
        result.put("paired_single_examples", pairedExamples);
        Files.writeString(Path.of(args[1]), new GsonBuilder().setPrettyPrinting().create().toJson(result) + "\n");
    }
}
