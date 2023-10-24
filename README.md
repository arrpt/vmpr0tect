# vmpr0tect
- Not throwing shade at vmprotect obv. Mine would be much shittier, lmao.
- Repository will contain both the source code and resources that I've used to learn
- Might be used as a reference for next year d4rkc0de ctf challenges who knows 🗿

## Nice Resources
https://www.youtube.com/watch?v=d_OFrP-m2xU

## Notes
1. VM entry/ exit
2. VM Dispatcher (FDE)----|
3. Handler table <--------| (performs lookup)

### Handler table Hardening Techniques
- Populate 256 entries (duplicating handler)
- Duplicate operations like virtual_add1, virtual_add2 -> add in x86_64 
- No central VM dispatcher
- Just get rid of explicit handler tables lol.

Instruction Encoding - `<opcode> <opcode> <next_handler_address>`