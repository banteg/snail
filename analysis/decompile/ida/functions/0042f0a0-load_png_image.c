/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: load_png_image @ 0x42f0a0 */
/* selector: load_png_image */

// Authored seven-argument cdecl PNG loader used only by rebuild_game_archive_if_needed. It reads through the statically linked libpng 1.2.5 API, returns an allocated pixel buffer plus dimensions and channel count, and copies an optional PNG background color to the caller.
int __cdecl load_png_image(
        char *png_path,
        unsigned __int8 **out_pixels,
        int *out_width,
        int *out_height,
        int *out_channels,
        unsigned __int8 *background_rgb,
        int file_offset)
{
  int result; // eax
  ObjectToonEdge *v8; // esi
  FrontendWidget *v9; // eax
  int rowbytes; // edi
  unsigned __int8 *v11; // eax
  unsigned __int8 *v12; // edi
  unsigned __int8 **v13; // ebx
  int v14; // edx
  unsigned __int8 **v15; // ecx
  unsigned __int8 *v16; // eax
  int v17; // edi
  unsigned int v18; // [esp+0h] [ebp-34h]
  int v19; // [esp+4h] [ebp-30h]
  unsigned __int8 Buffer[8]; // [esp+Ch] [ebp-28h] BYREF
  double v21; // [esp+14h] [ebp-20h] BYREF
  int v22; // [esp+1Ch] [ebp-18h]
  ObjectToonEdge *Stream; // [esp+20h] [ebp-14h]
  void *Block; // [esp+24h] [ebp-10h]
  int v25; // [esp+28h] [ebp-Ch] BYREF
  int v26; // [esp+2Ch] [ebp-8h] BYREF
  void *Src; // [esp+30h] [ebp-4h] BYREF
  int savedregs; // [esp+34h] [ebp+0h] BYREF

  Block = *out_pixels;
  if ( png_path != nullptr )
  {
    v8 = (ObjectToonEdge *)fopen(png_path, mode);
    Stream = v8;
    if ( v8 != nullptr )
    {
      if ( file_offset != 0 )
        fseek((File *)v8, file_offset, 0);
      fread(Buffer, 1u, 8u, (File *)v8);
      result = png_check_sig(Buffer, 8);
      if ( result != 0 )
      {
        v9 = (FrontendWidget *)png_create_read_struct(a125, 0, 0, 0);
        g_png_read_struct.title_widget = v9;
        if ( v9 != nullptr )
        {
          g_png_info_struct = png_create_info_struct(v9);
          if ( g_png_info_struct != nullptr )
          {
            if ( setjmp(
                   0,
                   (int)&savedregs,
                   (int)out_pixels,
                   (int)v8,
                   &g_png_read_struct.title_widget->list_kind,
                   0,
                   v18,
                   v19) != 0 )
              goto LABEL_14;
            png_init_io((int)g_png_read_struct.title_widget, (int)Stream);
            png_set_sig_bytes((int *__attribute__((__org_typedef(jmp_buf))))g_png_read_struct.title_widget, 8);
            png_read_info(
              (int *__attribute__((__org_typedef(jmp_buf))))g_png_read_struct.title_widget,
              g_png_info_struct);
            png_get_IHDR(
              (int *__attribute__((__org_typedef(jmp_buf))))g_png_read_struct.title_widget,
              (int)g_png_info_struct,
              out_width,
              out_height,
              &v25,
              &v26,
              nullptr,
              nullptr,
              nullptr);
            if ( v25 == 16 )
              png_set_strip_16((int)g_png_read_struct.title_widget);
            if ( v26 == 3 )
              png_set_expand((int)g_png_read_struct.title_widget);
            if ( v25 < 8 )
              png_set_expand((int)g_png_read_struct.title_widget);
            if ( png_get_valid((int)g_png_read_struct.title_widget, (int)g_png_info_struct, 16) != 0 )
              png_set_expand((int)g_png_read_struct.title_widget);
            if ( v26 == 0 || v26 == 4 )
              png_set_gray_to_rgb((int)g_png_read_struct.title_widget);
            if ( png_get_bKGD((int)g_png_read_struct.title_widget, (int)g_png_info_struct, &Src) != 0 )
            {
              png_set_background((int)g_png_read_struct.title_widget, Src, 2, 1, 1.0);
              *background_rgb = *((_BYTE *)Src + 2);
              background_rgb[1] = *((_BYTE *)Src + 4);
              background_rgb[2] = *((_BYTE *)Src + 6);
            }
            if ( png_get_gAMA((int)g_png_read_struct.title_widget, (int)g_png_info_struct, &v21) != 0 )
              png_set_gamma((int)g_png_read_struct.title_widget, 2.2, v21);
            png_read_update_info(
              (int *__attribute__((__org_typedef(jmp_buf))))g_png_read_struct.title_widget,
              (int)g_png_info_struct);
            png_get_IHDR(
              (int *__attribute__((__org_typedef(jmp_buf))))g_png_read_struct.title_widget,
              (int)g_png_info_struct,
              out_width,
              out_height,
              &v25,
              &v26,
              nullptr,
              nullptr,
              nullptr);
            rowbytes = png_get_rowbytes((int)g_png_read_struct.title_widget, (int)g_png_info_struct);
            v22 = rowbytes;
            *out_channels = (unsigned __int8)png_get_channels(
                                               (int)g_png_read_struct.title_widget,
                                               (int)g_png_info_struct);
            if ( Block != nullptr )
            {
              free(Block);
              Block = nullptr;
            }
            v11 = (unsigned __int8 *)malloc(rowbytes * *out_height);
            v12 = v11;
            Block = v11;
            if ( v11 == nullptr )
            {
LABEL_14:
              png_destroy_read_struct((int *)&g_png_read_struct, &g_png_info_struct, nullptr);
              *out_pixels = nullptr;
              return 0;
            }
            else
            {
              *out_pixels = v11;
              v13 = (unsigned __int8 **)malloc(4 * *out_height);
              if ( v13 != nullptr )
              {
                v14 = 0;
                if ( *out_height > 0 )
                {
                  v15 = v13;
                  v16 = v12;
                  do
                  {
                    v17 = v22;
                    *v15 = v16;
                    v16 += v17;
                    ++v14;
                    ++v15;
                  }
                  while ( v14 < *out_height );
                }
                png_read_image((struct png_struct_def *)g_png_read_struct.title_widget, v13);
                png_read_end((int *__attribute__((__org_typedef(jmp_buf))))g_png_read_struct.title_widget, nullptr);
                free(v13);
                fclose((File *)Stream);
                return 1;
              }
              else
              {
                png_destroy_read_struct((int *)&g_png_read_struct, &g_png_info_struct, nullptr);
                free(v12);
                *out_pixels = nullptr;
                return 0;
              }
            }
          }
          else
          {
            png_destroy_read_struct((int *)&g_png_read_struct, nullptr, nullptr);
            *out_pixels = nullptr;
            return 0;
          }
        }
        else
        {
          *out_pixels = nullptr;
          return 0;
        }
      }
      else
      {
        *out_pixels = nullptr;
      }
    }
    else
    {
      *out_pixels = nullptr;
      return 0;
    }
  }
  else
  {
    *out_pixels = nullptr;
    return 0;
  }
  return result;
}
