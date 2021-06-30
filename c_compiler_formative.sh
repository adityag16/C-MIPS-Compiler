#!/bin/bash
totaltest=0
passedtest=0
if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi

have_compiler=0
if [[ ! -f bin/c_compiler ]] ; then
    >&2 echo "Warning : cannot find compiler at path ${compiler}. Only checking C reference against python reference."
    have_compiler=1
fi

input_dir="c_compiler/formative"
working="tmp/formative_compiler"
mkdir -p ${working}

for i in ${input_dir}/* ; do
    for j in ${i}/*.c ; do
        base=$(echo $j | sed -E -e "s|${input_dir}/([^.]+)[.]c|\1|g"|sed "s|.*/||");
        base2=$(echo $base|sed "s|.*_||" );

        if [[ $base2 == "driver" ]] ; then
            continue;
        else
            tmp=${j/%.c/}
            gcc $j $tmp\_driver.c -o $working/$base
            $working/$base 
            REF_C_OUT=$?

            if [[ ${have_compiler} -eq 0 ]] ; then

                $compiler -S "$j" -o ${working}/$base.s

                mips-linux-gnu-gcc -mfp32 -o ${working}/$base.o -c ${working}/$base.s

                mips-linux-gnu-gcc -mfp32 -static -o ${working}/$base ${working}/$base.o $tmp\_driver.c

                qemu-mips ${working}/$base

                GOT_ASS_OUT=$?
                
               
       
            fi
        
            if [[ ${have_compiler} -ne 0 ]] ; then
                echo "$base, Fail, No C compiler/translator"
            elif [[ $REF_C_OUT -ne $GOT_ASS_OUT ]] ; then
                echo "$base, Fail, Expected ${REF_C_OUT}, got ${GOT_ASS_OUT}"
                ((totaltest++))
            else
                echo "$base, Pass"
                ((totaltest++))
                ((passedtest++))

            fi
            echo $'\n'


        fi

    done

   
done

echo "Passed ${passedtest} / ${totaltest}"
