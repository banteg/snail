# Asset Families

The current archive manifest shows these top-level groups:

- `X` (`144` files): plaintext `.X2` mesh and animation fragments in a DirectX `.x`-style text format
- `SEGMENTS` (`133` files): plaintext track or segment descriptions in `.TXT`
- `VOICE` (`112` files): voice-over scripts and `.OGG` clips
- `SPRITES` (`54` files): sprite textures and related text descriptors
- `LEVELS` (`53` files): plaintext level scripts
- `SFX2` (`36` files): sound effects, mainly `.OGG`
- `OBJECTS` (`25` files): object definitions and textures
- `BACKGROUNDS` (`19` files): background scripts and textures
- `GALAXY` (`18` files): skybox or galaxy art assets
- `MUSIC` (`6` files): background music and intro or menu tracks
- `INTRO` (`2` files): intro data
- `BASS.DLL` (`1` file): embedded Windows DLL payload

Extension counts from the decoded index:

- `.txt`: `204`
- `.ogg`: `153`
- `.x2`: `124`
- `.tga`: `121`
- `.dll`: `1`

## Verified Member Formats

- `.OGG`: standard Ogg Vorbis payloads, for example `MUSIC/1.OGG` starts with `OggS`
- `.TGA`: standard TGA images, for example `OBJECTS/FONT/FONT-MENU-HOVER.TGA` starts with an uncompressed true-color TGA header
- `.TXT`: plaintext scripts and object definitions, for example:
  - `VOICE/_VOICE.TXT` starts with `/* Voice Script */`
  - `BACKGROUNDS/MENUBG.TXT` is a small background script with keys like `Fog`, `Picture`, and `Landscape`
  - `OBJECTS/FONT3D/_OBJECT.TXT` is a text-based object or mesh definition with explicit vertex lists
- `.X2`: plaintext mesh fragments, for example `X/BLASTERLEFT-BASE-000.X2` begins with `Frame MeshMaterialList {`
- `.DLL`: `BASS.DLL` decodes to a normal PE payload beginning with `MZ`

Use the pages in this section for the details of each format family.
