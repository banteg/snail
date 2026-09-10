import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.data.FloatDataType;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
public class ProbeMobileABI extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs(); Path out=Path.of(args[0]); Files.createDirectories(out);
  Function target=getFunctionAt(toAddr(args[1]));
  DecompInterface di=new DecompInterface(); di.openProgram(currentProgram);
  Files.writeString(out.resolve("before.c"),di.decompileFunction(target,60,monitor).getDecompiledFunction().getC());
  StringBuilder evidence=new StringBuilder("image_base="+currentProgram.getImageBase()+"\ncompiler="+currentProgram.getCompilerSpec().getCompilerSpecID()+"\n");
  int changed=0;
  for(Function f:currentProgram.getFunctionManager().getFunctions(true)) {
   if(!f.getName().equals("Sqrt")&&!f.getName().equals("_Z4Sqrtf"))continue;
   evidence.append(f.getEntryPoint()+" before "+f.getPrototypeString(true,true)+" params ");
   for(Parameter p:f.getParameters())evidence.append(p.getVariableStorage()+" ");
   evidence.append("return "+f.getReturn().getVariableStorage()+"\n");
   f.updateFunction(null,new ReturnParameterImpl(FloatDataType.dataType,currentProgram.getRegister("r0"),currentProgram),Function.FunctionUpdateType.CUSTOM_STORAGE,true,SourceType.USER_DEFINED,new ParameterImpl("value",FloatDataType.dataType,currentProgram.getRegister("r0"),currentProgram));
   evidence.append(f.getEntryPoint()+" after "+f.getPrototypeString(true,true)+" params r0 return r0\n"); changed++;
  }
  if(changed==0)throw new IllegalStateException("no Sqrt");
  di.flushCache(); DecompileResults r=di.decompileFunction(target,60,monitor);
  if(!r.decompileCompleted())throw new IllegalStateException(r.getErrorMessage());
  Files.writeString(out.resolve("after.c"),r.getDecompiledFunction().getC());
  Files.writeString(out.resolve("receipt.txt"),evidence.toString());
  di.dispose();
 }
}
