# Twinkle::draw_twinkle @ 0x404070

Exact five-instruction `cRTwinkle::Draw()` body. Windows update callsites carry
the live `Twinkle*` in `ECX`, and Android independently preserves both the
authored method symbol and the same body: it constructs a temporary color while
otherwise leaving the receiver unused.
