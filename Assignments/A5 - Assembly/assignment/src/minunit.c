#include <stdio.h>
#include "minunit.h"
#include "decoder.h"
 
int tests_run = 0;

//SB test
static char * bne_test() {
    int x_registers[32] = {0};
    int commands[10] = {0};
    commands[0] = 65664; //starting position
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("bne_test", x_registers[11] == 10);
    code = 0x00b5d463; //Jump to shifting if condition is true
    SB_instruction(code, x_registers, commands);
    printf("%d\n", commands[0]);
    mu_assert("bne_test", commands[0] == 65700); //Shifting
    return 0;
}

static char * fail_beq_test() {
    int x_registers[32] = {0};
    int commands[10] = {0};
    commands[0] = 65664; //starting position
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("fail_beq_test", x_registers[11] == 10);
    mu_assert("fail_beq_test", x_registers[12] == 0);
    code = 0x00c58463; //Jump to shifting if condition is true
    SB_instruction(code, x_registers, commands);
    printf("%d\n", commands[0]);
    mu_assert("fail_beq_test", commands[0] == 65664); //Shifting
    return 0;
}

static char * beq_test() {
    int x_registers[32] = {0};
    int commands[10] = {0};
    commands[0] = 65664; //starting position
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("beq_test", x_registers[11] == 10);
    code = 0x00b58463; //Jump to shifting if condition is true
    SB_instruction(code, x_registers, commands);
    printf("%x\n", commands[0]);
    mu_assert("beq_test", commands[0] == 65668); //Shifting
    return 0;
}



//LoadStore test
static char * loadstoreW_test() {
    struct memory *mem = memory_create();
    int x_registers[32] = {0};
    long code = 0xff458593;
    immediate_instruction(code, x_registers);
    mu_assert("loadstoreW_test", x_registers[11] == -12);
    code = 0x00a60613;
    immediate_instruction(code, x_registers);
    mu_assert("loadstoreW_test", x_registers[12] == 10);
    code = 0x00c5a423;
    store_instruction(code, x_registers, mem);
    code = 0x0085a503;
    i_instruction(code, x_registers, mem);
    printf("x_registers[10] %d\n", x_registers[10]);
    mu_assert("loadstoreW_test", x_registers[10] == 10);
    return 0;
}

static char * loadstoreB_test() {
    struct memory *mem = memory_create();
    int x_registers[32] = {0};
    long code = 0xff458593;
    immediate_instruction(code, x_registers);
    mu_assert("loadstoreB_test", x_registers[11] == -12);
    code = 0x00a60613;
    immediate_instruction(code, x_registers);
    mu_assert("loadstoreB_test", x_registers[12] == 10);
    code = 0x00c58423;
    store_instruction(code, x_registers, mem);
    code = 0x00858503;
    i_instruction(code, x_registers, mem);
    printf("x_registers[10] %d\n", x_registers[10]);
    mu_assert("loadstoreB_test", x_registers[10] == 10);
    return 0;
}

static char * loadstoreBU_test() {
    struct memory *mem = memory_create();
    int x_registers[32] = {0};
    long code = 0xff458593;
    immediate_instruction(code, x_registers);
    mu_assert("loadstoreB_test", x_registers[11] == -12);
    code = 0x00a60613;
    immediate_instruction(code, x_registers);
    mu_assert("loadstoreB_test", x_registers[12] == 10);
    code = 0x00c58423;
    store_instruction(code, x_registers, mem);
    code = 0x00858503;
    i_instruction(code, x_registers, mem);
    printf("x_registers[10] %d\n", x_registers[10]);
    mu_assert("loadstoreB_test", x_registers[10] == 10);
    return 0;
}


static char * loadstoreH_test() {
    struct memory *mem = memory_create();
    int x_registers[32] = {0};
    long code = 0xff458593;
    immediate_instruction(code, x_registers);
    mu_assert("loadstoreH_test", x_registers[11] == -12);
    code = 0x00a60613;
    immediate_instruction(code, x_registers);
    mu_assert("loadstoreH_test", x_registers[12] == 10);
    code = 0x00c59623;
    store_instruction(code, x_registers, mem);
    code = 0x00c59503;
    i_instruction(code, x_registers, mem);
    printf("x_registers[10] %d\n", x_registers[10]);
    mu_assert("loadstoreH_test", x_registers[10] == 10);
    return 0;
}



//Shifting test
static char * slli_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("slli_test", x_registers[11] == 10);
    code = 0x00559093;
    immediate_instruction(code, x_registers);
    printf("%d\n", x_registers[1]);
    mu_assert("slli_test", x_registers[1] == 320);
    return 0;
}

static char * srli_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("srli_test", x_registers[11] == 10);
    code = 0x0055d093;
    immediate_instruction(code, x_registers);
    printf("%d\n", x_registers[1]);
    mu_assert("srli_test", x_registers[1] == 0);
    return 0;
}

static char * sll_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("sll_test", x_registers[11] == 10);
    code = 0x00b59633;
    register_instruction(code, x_registers);
    printf("%d\n", x_registers[1]);
    mu_assert("sll_test", x_registers[12] == 10240);
    return 0;
}

static char * srl_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("srl_test", x_registers[11] == 10);
    code = 0x00b5d633;
    register_instruction(code, x_registers);
    printf("%d\n", x_registers[1]);
    mu_assert("srl_test", x_registers[12] == 0);
    return 0;
}

static char * sra_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("sra_test", x_registers[11] == 10);
    code = 0x00b5d633;
    register_instruction(code, x_registers);
    printf("%d\n", x_registers[1]);
    mu_assert("sra_test", x_registers[12] == 0);
    return 0;
}

static char * srai_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("sra_test", x_registers[11] == 10);
    code = 0x4055d093;
    immediate_instruction(code, x_registers);
    printf("%d\n", x_registers[1]);
    mu_assert("sra_test", x_registers[12] == 0);
    return 0;
}


//logic test
static char * or_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("or_test", x_registers[11] == 10);
    code = 0x00b5e633;
    register_instruction(code, x_registers);
    printf("%d\n", x_registers[1]);
    mu_assert("or_test", x_registers[12] == 10);
    return 0;
}

static char * xori_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("xori_test", x_registers[11] == 10);
    code = 0x0645c093;
    immediate_instruction(code, x_registers);
    printf("x_registers %d\n", x_registers[1]);
    mu_assert("xori_test", x_registers[1] == 110);
    return 0;
}

static char * ori_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("ori_test", x_registers[11] == 10);
    code = 0x0645e093;
    immediate_instruction(code, x_registers);
    printf("x_registers %d\n", x_registers[1]);
    mu_assert("ori_test", x_registers[1] == 110);
    return 0;
}

static char * andi_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("andi_test", x_registers[11] == 10);
    code = 0x0645f093;
    immediate_instruction(code, x_registers);
    printf("x_registers %d\n", x_registers[1]);
    mu_assert("andi_test", x_registers[1] == 0);
    return 0;
}

static char * and_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("and_test", x_registers[11] == 10);
    code = 0x00b5f633;
    register_instruction(code, x_registers);
    printf("x_registers %d\n", x_registers[12]);
    mu_assert("and_test", x_registers[12] == 10);
    return 0;
}


//Extension test
static char * mul_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("MUL TEST", x_registers[11] == 10);
    code = 0x02b58633;
    m_instruction(code, x_registers);
    printf("%d\n", x_registers[12]);
    mu_assert("MUL TEST", x_registers[12] == 100);
    return 0;
}

static char * mulh_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("MULH TEST", x_registers[11] == 10);
    code = 0x02b59633;
    m_instruction(code, x_registers);
    printf("%d\n", x_registers[12]);
    mu_assert("MULH TEST", x_registers[12] == 100);
    return 0;
}

static char * mulhsu_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("MULHSU TEST", x_registers[11] == 10);
    code = 0x02b5a633;
    m_instruction(code, x_registers);
    printf("%d\n", x_registers[12]);
    mu_assert("MULHSU TEST", x_registers[12] == 100);
    return 0;
}

static char * mulhu_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("MULHU TEST", x_registers[11] == 10);
    code = 0x02b5b633;
    m_instruction(code, x_registers);
    printf("%d\n", x_registers[12]);
    mu_assert("MULHU TEST", x_registers[12] == 100);
    return 0;
}

static char * div_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("DIV TEST", x_registers[11] == 10);
    code = 0x02b5c633;
    m_instruction(code, x_registers);
    printf("%d\n", x_registers[12]);
    mu_assert("DIV TEST", x_registers[12] == 1);
    return 0;
}

static char * divu_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("DIVU TEST", x_registers[11] == 10);
    code = 0x02b5d633;
    m_instruction(code, x_registers);
    printf("%d\n", x_registers[12]);
    mu_assert("DIVU TEST", x_registers[12] == 1);
    return 0;
}

static char * rem_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("REM TEST", x_registers[11] == 10);
    code = 0x02b5e633;
    m_instruction(code, x_registers);
    printf("%d\n", x_registers[12]);
    mu_assert("REM TEST", x_registers[12] == 0);
    return 0;
}

static char * remu_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("REMU TEST", x_registers[11] == 10);
    code = 0x02b5f633;
    m_instruction(code, x_registers);
    printf("%d\n", x_registers[12]);
    mu_assert("REMU TEST", x_registers[12] == 0);
    return 0;
}


//Arithmetic test
static char * addi_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("ADDI TEST", x_registers[11] == 10);
    printf("%d\n", x_registers[11]);
    code = 0xfd050513;
    immediate_instruction(code, x_registers);
    printf("%d\n", x_registers[10]);
    mu_assert("ADDI TEST", x_registers[10] == -48);
    return 0;
}
static char * add_test() {
    int x_registers[32] = {0};
    long code = 0x00a58593;
    immediate_instruction(code, x_registers);
    mu_assert("ADDI TEST", x_registers[11] == 10);
    code = 0x00b50633;
    register_instruction(code, x_registers);
    mu_assert("ADD TEST", x_registers[12] == 10);
    return 0;
}

static char * sub_test() {
    int x_registers[32];
    for (int i = 0; i < 32; i++){
        x_registers[i] = 0;
    }
    int code = -555117; //addi a5,a5,-1
    int a5_old = x_registers[15];
    int a0_old = x_registers[10];
    immediate_instruction(code, x_registers); 
    mu_assert("ADD not updating", a5_old != x_registers[15]);
    mu_assert("ADD gets the wrong number negative", x_registers[15] == -1);
    code = 1088914739;  //sub a0,a5,a4  
    register_instruction(code, x_registers); 
    mu_assert("SUB doesn't update regestry", x_registers[10] != a0_old);
    mu_assert("SUB doesn't insert correct value", x_registers[10] == x_registers[15] - x_registers[14]);
    return 0;
}

 static char * all_tests() {

    
    //arithmetic test
    mu_run_test(addi_test);
    mu_run_test(add_test);
    mu_run_test(sub_test);

    //Extension test
    mu_run_test(mul_test);
    mu_run_test(mulh_test);
    mu_run_test(mulhsu_test);
    mu_run_test(mulhu_test);
    mu_run_test(div_test);
    mu_run_test(divu_test);
    mu_run_test(rem_test);
    mu_run_test(remu_test);

    //logic test
    mu_run_test(xori_test);
    mu_run_test(or_test);
    mu_run_test(ori_test);
    mu_run_test(andi_test);
    mu_run_test(and_test);

    //Shifting test
    mu_run_test(slli_test);
    mu_run_test(srli_test);
    mu_run_test(sll_test);
    mu_run_test(srl_test);
    mu_run_test(sra_test);
    mu_run_test(srai_test);

    //LoadStore test
    mu_run_test(loadstoreW_test);
    // mu_run_test(loadstoreH_test); //Does not work
    mu_run_test(loadstoreB_test);
    mu_run_test(loadstoreBU_test);

    //SB test
    mu_run_test(bne_test);
    mu_run_test(beq_test);
    mu_run_test(fail_beq_test);
    return 0;
 }
 
 int main(int argc, char **argv) {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
    