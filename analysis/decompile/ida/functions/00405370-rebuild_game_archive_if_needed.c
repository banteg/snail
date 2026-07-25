/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rebuild_game_archive_if_needed @ 0x405370 */
/* selector: rebuild_game_archive_if_needed */

// When `SnailMail.dat` is missing but `SnailMail.dam` exists, decodes the legacy ArchiveIndex and its 12-byte entries, repacks TGA entries through the PNG loader into typed TGA headers plus inline pixels, copies other payloads unchanged, writes the rebuilt `SnailMail.dat`, and deletes the old `.dam` plus temporary `0.png`.
void __cdecl rebuild_game_archive_if_needed()
{
  SerializedArchiveIndex *rebuilt_index; // ebx
  int initial_payload_offset; // ebp
  char *payload_cursor; // ebp
  bool v3; // cc
  int *source_byte_count_cursor; // ebx
  char *rebuilt_base; // esi
  const char *entry_path_for_log; // edi
  int payload_end_address; // ebp
  __int16 v8; // ax
  int v9; // edx
  int v10; // esi
  int v11; // eax
  int y; // edi
  int source_pixel_offset; // ecx
  int destination_pixel_offset; // eax
  int converted_size; // edx
  int png_channels; // [esp+0h] [ebp-234h] BYREF
  unsigned __int8 *png_pixels; // [esp+4h] [ebp-230h] BYREF
  int *rebuilt_data_offset_cursor; // [esp+8h] [ebp-22Ch]
  SerializedArchiveIndex *rebuilt_index_saved; // [esp+Ch] [ebp-228h]
  int png_width; // [esp+10h] [ebp-224h] BYREF
  SerializedArchiveIndex *source_index; // [esp+14h] [ebp-220h]
  int png_height; // [esp+18h] [ebp-21Ch] BYREF
  int x; // [esp+1Ch] [ebp-218h]
  int source_to_rebuilt_delta; // [esp+20h] [ebp-214h]
  int entry_index; // [esp+24h] [ebp-210h]
  int dam_size; // [esp+28h] [ebp-20Ch] BYREF
  char *entry_path; // [esp+2Ch] [ebp-208h]
  unsigned int png_background_rgb; // [esp+30h] [ebp-204h] BYREF
  unsigned __int8 entry_stem[512]; // [esp+34h] [ebp-200h] BYREF

  if ( !file_exists(FileName) && file_exists(aSnailmailDam) )
  {
    rebuilt_index = (SerializedArchiveIndex *)malloc(0x2625A00u);
    rebuilt_index_saved = rebuilt_index;
    source_index = (SerializedArchiveIndex *)load_file_bytes_allocating(aSnailmailDam, &dam_size);
    toggle_archive_high_bit_in_place((char *)source_index, dam_size);
    qmemcpy(rebuilt_index, source_index, source_index->entries[0].data_offset);
    initial_payload_offset = rebuilt_index->entries[0].data_offset;
    png_pixels = nullptr;
    payload_cursor = (char *)rebuilt_index + initial_payload_offset;
    v3 = source_index->count <= 0;
    entry_index = 0;
    if ( !v3 )
    {
      rebuilt_data_offset_cursor = &rebuilt_index->entries[0].data_offset;
      source_byte_count_cursor = &source_index->entries[0].byte_count;
      source_to_rebuilt_delta = (char *)rebuilt_index_saved - (char *)source_index;
      do
      {
        rebuilt_base = (char *)rebuilt_index_saved;
        entry_path = (char *)rebuilt_index_saved + *(source_byte_count_cursor - 2);
        entry_path_for_log = entry_path;
        if ( classify_archive_entry_extension((unsigned __int8 *)entry_path, entry_stem) == ARCHIVE_ENTRY_EXTENSION_TGA )
        {
          save_file_bytes_with_optional_archive_scramble(
            a0Png,
            (char *)source_index + *(source_byte_count_cursor - 1),
            *source_byte_count_cursor,
            0);
          load_png_image(
            a0Png,
            &png_pixels,
            &png_width,
            &png_height,
            &png_channels,
            (unsigned __int8 *)&png_background_rgb,
            0);
          *rebuilt_data_offset_cursor = payload_cursor - rebuilt_base;
          payload_cursor[7] = 0;
          payload_cursor[6] = 0;
          payload_cursor[5] = 0;
          payload_cursor[4] = 0;
          payload_cursor[3] = 0;
          payload_cursor[1] = 0;
          *payload_cursor = 0;
          v8 = png_height;
          payload_cursor[17] = 8;
          *((_WORD *)payload_cursor + 7) = v8;
          payload_cursor[2] = 2;
          payload_cursor[16] = 8 * png_channels;
          *((_WORD *)payload_cursor + 6) = png_width;
          *((_WORD *)payload_cursor + 4) = 0;
          *((_WORD *)payload_cursor + 5) = 0;
          v9 = png_width;
          v10 = png_channels;
          x = 0;
          v11 = png_height;
          if ( png_width > 0 )
          {
            do
            {
              y = 0;
              if ( v11 > 0 )
              {
                do
                {
                  source_pixel_offset = v10 * (x + v9 * y);
                  destination_pixel_offset = v10 * (x + v9 * (v11 - y - 1));
                  payload_cursor[destination_pixel_offset + 20] = png_pixels[source_pixel_offset];
                  payload_cursor[destination_pixel_offset + 19] = png_pixels[source_pixel_offset + 1];
                  payload_cursor[destination_pixel_offset + 18] = png_pixels[source_pixel_offset + 2];
                  v10 = png_channels;
                  if ( png_channels == 4 )
                  {
                    payload_cursor[destination_pixel_offset + 21] = png_pixels[source_pixel_offset + 3];
                    v10 = png_channels;
                  }
                  v11 = png_height;
                  v9 = png_width;
                  ++y;
                }
                while ( y < png_height );
              }
              ++x;
            }
            while ( x < v9 );
            entry_path_for_log = entry_path;
          }
          converted_size = v10 * v11 * v9 + 20;
          *(int *)((char *)source_byte_count_cursor + source_to_rebuilt_delta) = converted_size;
          payload_cursor += (int)&payload_cursor[converted_size] % 4 + converted_size;
          printf("extracting %s\n", entry_path_for_log);
        }
        else
        {
          qmemcpy(payload_cursor, (char *)source_index + *(source_byte_count_cursor - 1), *source_byte_count_cursor);
          *rebuilt_data_offset_cursor = payload_cursor - (char *)rebuilt_index_saved;
          payload_end_address = (int)&payload_cursor[*source_byte_count_cursor];
          *(int *)((char *)source_byte_count_cursor + source_to_rebuilt_delta) = *source_byte_count_cursor;
          payload_cursor = (char *)(payload_end_address % 4 + payload_end_address);
        }
        rebuilt_data_offset_cursor += 3;
        source_byte_count_cursor += 3;
        ++entry_index;
      }
      while ( entry_index < source_index->count );
      rebuilt_index = rebuilt_index_saved;
    }
    save_file_bytes_with_optional_archive_scramble(FileName, rebuilt_index, payload_cursor - (char *)rebuilt_index, 1u);
    delete_file_path(aSnailmailDam);
    delete_file_path(a0Png);
    free(rebuilt_index);
  }
}
