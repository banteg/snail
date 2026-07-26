/*
 * mangled: _Z19ObjectProcWorldInitbP8cRObject
 * demangled: ObjectProcWorldInit(bool, cRObject*)
 * address: 0003c2f8
 * size: 80
 */

/* ObjectProcWorldInit(bool, cRObject*) */

void ObjectProcWorldInit(bool param_1,cRObject *param_2)

{
  cRObject::RequestVertices(param_2,20000);
  cRObject::RequestFaceQuads(param_2,10000);
  if (!param_1) {
    cRObject::RequestColours(param_2);
    *(uint *)param_2 = *(uint *)param_2 | 0x10000;
  }
  cRObject::RequestFaceQuadTextureGroups(param_2,5000);
  return;
}
