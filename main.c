#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include <string.h>


int8_t* generate_look_up_table(uint64_t number_of_generated);
uint64_t number_to_offset(uint64_t number);
uint64_t offset_to_number(uint64_t offset);


int8_t* generate_look_up_table(uint64_t number_of_generated){
    int8_t* ret = (uint8_t*) malloc(number_of_generated*sizeof(uint8_t));
    //by default numbers are assumed to be primes and they may be proven to be non prime
    memset(ret, 1, number_of_generated*sizeof(uint8_t));


    uint64_t last_number = 3 + number_of_generated*2;
    for(uint64_t considered_number=3; considered_number<number_of_generated; considered_number+=2){
        if(ret[number_to_offset(considered_number)]){
            uint64_t base_offset = number_to_offset(considered_number);
            //even numbers are ommitted; both these divisible and non divisible by considered_number;
            //threfore offset_step can be equal to considered_number
            uint64_t offset_step = considered_number;
            for(int offset=base_offset+offset_step; offset<number_of_generated; offset+=offset_step){
                //the stored number is not prime as being divisible by considered_number
                ret[offset]=0;
            }
        }
    }
    return ret;
}

/*
A function returning 1 if checked number is prime (the information is extracted from look-up table).
The checked number is translated to memory offset in a look-up table.
*/
uint8_t is_prime(uint64_t checked, int8_t* look_up_table){
    return look_up_table[number_to_offset(checked)];
}


/*
Translates a number to the offset to access the corresponding datum in the look-up table
e.g.    about 3 is stored in look_up_table[0]
        about 5 is stored in look_up_table[1]
        about 7 is stored in look_up_table[2]

IMPORTANT note: the translation account for the auto-floor of division as all considered numbers are odd
*/
uint64_t number_to_offset(uint64_t number){
    return (number/2-1);
}

/*
A translation function reverse to number_to_offset

IMPORTANT note: the translation account for the auto-floor of division as all considered numbers are odd
*/
uint64_t offset_to_number(uint64_t offset){
    return (offset*2+3);
}


//an example usage of look-up table
int main(){
    uint64_t number_of_generated=1000;
    int8_t* look_up_table = generate_look_up_table(number_of_generated);
    for(uint64_t offset=0; offset<number_of_generated; ++offset){
        uint64_t number = offset_to_number(offset);
        if(1 == look_up_table[offset]){
            printf("%" PRIu64 "\tis prime\n", number);
        }
        else{
            printf("%" PRIu64 "\tis not prime\n", number);
        }
    }
}