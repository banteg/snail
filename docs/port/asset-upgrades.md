# Ultimate asset upgrades

Ultimate keeps Android's content and palette while using matching higher-resolution
art where it exists. Rebuild with `uv run snail port extras`. In addition to the
Android sources and PC archive, this now requires the extracted iPhone 1.9 app at
`artifacts/asset-scout/src/ios19/Payload/iSM103010_1.app`, or `--ios-root DIR`.
All vendor art and generated archives stay outside Git.

## Upgraded textures

| Extras texture | Previous pixels | New pixels | Source |
| --- | --- | --- | --- |
| `Objects/World00/Track4`–`6.tga` | 128×128 | 256×256 | iPhone 1.9 `objects_world00_hi_surface4`–`6.tga`, first tile |
| `Objects/World00/Slide4`–`6.tga` | 128×128 | 256×256 | Same atlases, second tile |
| `Backgrounds/SpacePro.tga` | 512×256 | 512×512 | Android `BACKGROUNDS/SPACEPRO.JPG`, without vertical reduction |
| `Backgrounds/SpacePro2.tga` | 512×256 | 512×512 | Android `BACKGROUNDS/SPACEPRO2.JPG`, without vertical reduction |

The iPhone HD atlases are 1024×256; the Android and older iPhone atlases are
512×128. TGA decoding needs a red/blue swap for **both** 24-bit and 32-bit iPhone
atlases. After that correction, the first two tiles of HD sets 0–3 are
pixel-identical to all eight PC `Track0`–`3` / `Slide0`–`3` textures. This checks
both the art's lineage and the crop/channel convention. The extras pack does not
replace those PC textures.

HD sets 5 and 6 are copied at native resolution after channel correction. Set 4
is darker and more magenta than Android. `match_surface_palette` computes the
signed RGB difference between Android's tile and the HD tile reduced to 128×128,
enlarges only that correction with bilinear filtering, then adds it to the
original HD pixels. This preserves the HD detail while matching Android's red
colour field. Track and slide are processed independently to avoid atlas-edge
bleeding; floating-point differences prevent unsigned clipping before addition.
It is a derived colour match, not a claim that an exact Android HD master exists.
Reduced back to Android size, mean absolute error per channel is below 0.5/255
for the track and 1.4/255 for the slide.

The Pro skies already use full-image normalized UVs, so retaining 512 source rows
needs no rendering or framing change. The other Pro background conversions keep
their existing PC menu/split-image UV layouts.

### Source identities

SHA-256 of the iPhone 1.9 files, before decoding or palette conversion:

| Filename | SHA-256 |
| --- | --- |
| `objects_world00_hi_surface4.tga` | `100b9935f03e905a38591d475ea3a81dc027a55a3b993e8748e20e0b5b20f630` |
| `objects_world00_hi_surface5.tga` | `0ade32921f8f8be04ec4c8171d5367e8baf52e172b35cd4ced8014cf5ac9ae1f` |
| `objects_world00_hi_surface6.tga` | `02e21b125372675ead34aa1411a1ab06fb3844dfe9a90bacee23c71d860c9f0f` |

## Other candidates checked

A filename/stem audit compared the PC archive's 121 images with decoded Android,
iPhone 1.5, iPhone 1.9 and iPad images, including alternate PNG/JPEG extensions:
243 matching image pairs. The extras pack's mobile-only images were also checked.
Raw PVRTC/PVR files were not decoded in this audit; their file size alone is not
evidence of a usable higher-detail replacement.

| Candidate | Finding | Decision |
| --- | --- | --- |
| Pro galaxy borders, level selector, line, trampoline ring, fringe-colour lookup | The other mobile releases' decoded equivalents have the same dimensions as Android. | Keep the current assets. |
| `Sprites/LoadingBarOn.tga` | Mobile is 512×64 versus PC 256×32, but redraws the yellow bar as green and changes its surrounding art. | Not a matching resolution upgrade. |
| `Objects/Universe/Fringe.tga` | Mobile is 8×8 versus PC 4×4, with a different alpha profile. | Changes the fringe fade; belongs to the presentation decisions in issue #109. |
| `Sprites/Overlay.tga` | Mobile is 32×32 black; PC is 2×2 white. | A different renderer convention, not added detail. |
| Four shared postal skies | Android is 512×512 versus PC 512×256, but closely reproduces the PC art resampled and JPEG-compressed (0.66–2.08/255 mean error after resizing to PC size). | No demonstrated added detail; keep the PC masters and their existing framing. |
| `Backgrounds/Starmapbg` | Mobile has the galaxies painted into its image; the PC draws them separately. | A layout/rendering difference, not a drop-in texture upgrade. |
| Pro star map and splash | No larger decoded mobile source found; conversion adapts phone art to the existing PC menu UV contracts. | Keep the current conversion. |

## Verification and distribution

`tests/test_port_mobile_assets.py` checks channel order in both TGA depths,
orientation, crop boundaries, retention of sub-reference-resolution detail,
PC/HD pixel identity, the derived red palette, and lossless Pro sky conversion.
`tests/test_port_mobile_backgrounds.py` checks the dimensions received by the
browser reactor's texture upload and its full-image/flip UVs.

The rebuilt archive has the same 266 entries; only the eight textures above
change. Level scripts, segments, audio and all other assets remain byte-identical.
Original's assets and gameplay code are untouched.

The published asset bundle remains pinned by `port/deploy-assets.json`. To ship
the upgrade, package and upload a new versioned bundle and update that manifest
using the existing [deployment workflow](README.md#hosting); a source change alone
does not replace an already published bundle.
