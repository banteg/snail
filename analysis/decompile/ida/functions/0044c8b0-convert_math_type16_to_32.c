/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: convert_math_type16_to_32 @ 0x44c8b0 */
/* selector: convert_math_type16_to_32 */

// Converts one signed-16 gameplay math value back into float form by scaling with `scale / 65536`. Android symbols match this helper to `MathType16to32(short, float)`, and both Android and Windows only xref it from the SubGoldy update path.
double __cdecl sub_44C8B0(__int16 a1, float a2)
{
  return a2 * 0.000015258789 * (double)a1;
}

