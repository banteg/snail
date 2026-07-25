/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_snail_hotspots @ 0x445d50 */

00445d50        struct Snail* snail_1 = snail
00445d53        struct Object* hotspot_model = snail->snail_hotspot_body.bod.object
00445d5f        char** hotspot_name_cursor = &data_4a4aa0
00445d64        struct SnailHotspotLocalZCursorView* hotspot_local_z_cursor = &snail->snail_hotspots_local[0].z
00445d76        *hotspot_local_z_cursor = struct SnailHotspotLocalZCursorView {
    .z = 0
    .y = 0
    .x = 0
}
00445d7e        struct TextureRef* j = get_or_create_texture_ref(&g_texture_refs, *hotspot_name_cursor, nullptr, 0)
00445d83        int32_t facequad_count = hotspot_model->facequad_count
00445d86        int32_t ecx = 0
00445d8a        if (facequad_count s<= 0)
00445da6        label_445da6:
00445da6        report_errorf("Cannot find HotPoint Texture %s", *hotspot_name_cursor)
00445d8f        struct ObjectFaceQuadTextureCursorView* hotspot_face_texture_cursor = &hotspot_model->facequads->texture_ref
00445d94        while (hotspot_face_texture_cursor->texture_ref != j)
00445d96        ecx += 1
00445d97        hotspot_face_texture_cursor = &hotspot_face_texture_cursor[1]
00445d9c        if (ecx s>= facequad_count)
00445d9c        goto label_445da6
00445db9        int32_t eax_2 = 0
00445dbb        eax_2.w = hotspot_model->facequads[ecx].vertex_0
00445dc0        struct Vec3* vertices = hotspot_model->vertices
00445dc6        int32_t eax_3 = eax_2 * 3
00445dcc        struct Vec3* hotspot_source_vertex = vertices + (eax_3 << 2)
00445dcf        hotspot_local_z_cursor->x = fconvert.s(fconvert.t(hotspot_local_z_cursor->x) + fconvert.t(*(vertices + (eax_3 << 2))))
00445dd8        hotspot_local_z_cursor->y = fconvert.s(fconvert.t(hotspot_source_vertex->y) + fconvert.t(hotspot_local_z_cursor->y))
00445de0        hotspot_local_z_cursor->z = fconvert.s(fconvert.t(hotspot_source_vertex->z) + fconvert.t(hotspot_local_z_cursor->z))
00445df0        *hotspot_local_z_cursor = *hotspot_local_z_cursor
00445df2        hotspot_name_cursor = &hotspot_name_cursor[1]
00445df5        hotspot_local_z_cursor = &hotspot_local_z_cursor[1]
00445dfe        do while (hotspot_name_cursor s< "X/CameraIntroTalk")
00445e18        snail->snail_hotspots_local[0x12].y = fconvert.s(fconvert.t(snail->snail_hotspots_local[0x12].y) + fconvert.t(0.300000012f))
00445e1f        return
