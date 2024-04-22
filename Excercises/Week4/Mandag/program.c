int main(){
    for (I=0; I<8; I++)
        for (J=0; J<8000; J++)
            A[I][J]=B[I][0]+A[J][I];
}

//5.1.4 [5] <§5.1> Which variable references exhibit temporal locality?
        // the temporal efficiency is quite good as the B value only gets updated
        // once every 8k steps, you could improve the efficiency by storing b in a temporary
        // value like this:
void TemporalImprovement(){
    for (I=0; I<8; I++)
        int r =  B[I][0]
        for (J=0; J<8000; J++)
            A[I][J]=r+A[J][I];
}
// 5.1.5 [5] <§5.1> Which variable references exhibit spatial locality?
        // It is inefficient as C is row major, which means that every time
        // the A value needs to be accessed it needs to jump 8k values in the memory
        // It would be more efficient to swap the I and J for loop:
    void SpacialImprovement(){
    for (J=0; J<8000; J++)
        for (I=0; I<8; I++)
            A[I][J]=r+A[J][I];
}
    // Matlab is collumn major, which means that it goes through collumns first
    // therefore you can run this code more efficiently than in C as you can do
    // both spacial and temporal locality:

    //  Matlab example:
    //     for I=1:8
    //         int r = B(I,0)
    //         for J=1:8000
    //             A(I,J)=)r+A(J,I);
    //         end
    //     end


// 5.1.6 [15] <§5.1> How many 16-byte cache blocks are needed to store all 64-bit 
// matrix elements being referenced using Matlab’s matrix storage? How many using 
// C’s matrix storage? (Assume each row contains more than one element.)
        // 8*8000 = 64.000 elements, but as we can store two elements in each we
        // only need 32000 elements