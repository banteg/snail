/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_animation @ 0x430a70 */
/* selector: request_object_animation */

// Void Windows `cRObject::RequestAnim(int, cRBodPos*, float, int)`: validates borrowed keyframe Objects, allocates and retains the ObjectAnimation/frame graph, interpolates each vertex as a scaled next-minus-current delta, and regenerates per-frame facequad normals.
void __thiscall request_object_animation(
        Object *object,
        int32_t keyframe_count,
        XAnimationKeyframe *keyframes,
        float progress_step,
        int32_t flags)
{
  int32_t v5; // eax
  int32_t vertex_count; // edx
  Object **v9; // ecx
  int v10; // ebp
  ObjectAnimation *tracked_memory; // eax
  int v12; // edi
  int32_t *p_frame_number; // ecx
  Object **p_object; // ebx
  double X; // st7
  Object *v16; // edx
  Object *v17; // eax
  int v18; // edx
  float *p_x; // ecx
  Vec3 *v20; // eax
  float *v21; // ecx
  Vec3 *vertices; // eax
  double v23; // st7
  double v24; // st6
  float *v25; // eax
  Vec3 *v26; // eax
  ObjectAnimation *animation; // eax
  float v28; // [esp+18h] [ebp-38h]
  float i; // [esp+18h] [ebp-38h]
  int v30; // [esp+1Ch] [ebp-34h]
  int32_t v31; // [esp+20h] [ebp-30h]
  int32_t *v32; // [esp+24h] [ebp-2Ch]
  float v33; // [esp+28h] [ebp-28h]
  float v34; // [esp+2Ch] [ebp-24h]
  float v35; // [esp+30h] [ebp-20h]
  float v36; // [esp+34h] [ebp-1Ch]
  float v37; // [esp+3Ch] [ebp-14h]
  float v38; // [esp+40h] [ebp-10h]
  float v39; // [esp+48h] [ebp-8h]
  float v40; // [esp+4Ch] [ebp-4h]
  XAnimationKeyframe *keyframesa; // [esp+58h] [ebp+8h]
  int32_t progress_stepa; // [esp+5Ch] [ebp+Ch]
  int32_t flagsa; // [esp+60h] [ebp+10h]

  v5 = 0;
  if ( keyframe_count <= 0 )
  {
LABEL_5:
    object->flags |= 0x200000u;
    v10 = (__int64)(1.0 / progress_step);
    v30 = v10;
    tracked_memory = (ObjectAnimation *)allocate_tracked_memory(20, aObjectAnimatio);
    object->animation = tracked_memory;
    tracked_memory->generated_frame_count = v10;
    object->animation->flags = flags;
    object->animation->progress = 0.0;
    object->animation->progress_step = progress_step;
    keyframesa = nullptr;
    object->animation->frames = (ObjectAnimationFrame **)allocate_tracked_memory(4 * v10, aObjectAnimatio_0);
    flagsa = keyframes->frame_number;
    if ( keyframe_count == 1 )
      progress_stepa = keyframes->frame_number;
    else
      progress_stepa = keyframes[1].frame_number;
    v12 = 0;
    if ( v10 > 0 )
    {
      v33 = (float)v10;
      p_frame_number = &keyframes[keyframe_count - 1].frame_number;
      p_object = &keyframes->object;
      v32 = p_frame_number;
      do
      {
        object->animation->frames[v12] = (ObjectAnimationFrame *)allocate_tracked_memory(8, aObjectAnimatio_1);
        object->animation->frames[v12]->vertices = (Vec3 *)allocate_tracked_memory(
                                                             12 * object->vertex_count,
                                                             aObjectAnimatio_2);
        object->animation->frames[v12]->facequad_normals = (Vec3 *)allocate_tracked_memory(
                                                                     24 * object->facequad_count,
                                                                     aObjectAnimatio_3);
        X = (double)(v12 * *v32) / v33;
        v28 = X;
        if ( (int)(__int64)floor(X) >= progress_stepa && (int)keyframesa < keyframe_count - 1 )
        {
          v16 = p_object[54];
          v17 = p_object[86];
          p_object += 32;
          keyframesa = (XAnimationKeyframe *)((char *)keyframesa + 1);
          flagsa = (int32_t)v16;
          progress_stepa = (int32_t)v17;
        }
        v18 = 0;
        v31 = 0;
        for ( i = (v28 - (double)flagsa) / (double)(progress_stepa - flagsa); v31 < object->vertex_count; ++v31 )
        {
          if ( keyframe_count == 1 )
          {
            p_x = &(*p_object)->vertices[v18].x;
            v20 = &object->animation->frames[v12]->vertices[v18];
            v20->x = *p_x;
            v20->y = p_x[1];
            v10 = v30;
            v20->z = p_x[2];
          }
          else
          {
            v21 = &p_object[32]->vertices[v18].x;
            vertices = (*p_object)->vertices;
            v23 = *v21 - vertices[v18].x;
            v24 = v21[1] - vertices[v18].y;
            v25 = &vertices[v18].x;
            v37 = v24;
            v38 = v21[2] - v25[2];
            v39 = v37 * i;
            v40 = v38 * i;
            v34 = v23 * i + *v25;
            v35 = v39 + v25[1];
            v36 = v40 + v25[2];
            v26 = &object->animation->frames[v12]->vertices[v18];
            v26->x = v34;
            v26->y = v35;
            v26->z = v36;
          }
          ++v18;
        }
        animation = object->animation;
        object->vertices = animation->frames[v12]->vertices;
        object->facequad_normals = animation->frames[v12]->facequad_normals;
        calc_object_facequad_normals(object);
        ++v12;
      }
      while ( v12 < v10 );
    }
    object->animation->progress = 0.0;
  }
  else
  {
    vertex_count = object->vertex_count;
    v9 = &keyframes->object;
    while ( (*v9)->vertex_count == vertex_count )
    {
      ++v5;
      v9 += 32;
      if ( v5 >= keyframe_count )
        goto LABEL_5;
    }
    report_errorf("Anim tween Vertices don't match Frame %i", keyframes[v5].frame_number);
  }
}
