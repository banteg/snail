/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: convert_math_type32_to_16 @ 0x44c890 */
/* selector: convert_math_type32_to_16 */

// Converts one float into the shared signed-16 gameplay math representation by scaling with `65536 / scale` and truncating. Android symbols match this helper to `MathType32to16(float, float)`, and both Android and Windows only xref it from the SubGoldy update path.
__int64 __cdecl sub_44C890(float a1, float a2)
{
  return (__int64)(65536.0 / a2 * a1);
}

