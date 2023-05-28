// Author: Jonghyeok Park
// E-mail: akindo19@skku.edu


// FA instance has three memeber variables
// 1) logical address range, 2) list of flash blocks, 3) current write_porinter
// Page mapping table has FA bit !!!
// Probing: input (LSA) to output(FA instances)

void flashalloc(unsigned int offset, unsigned int len);
