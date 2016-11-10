for var in "$@"
do
    cp "$var" ../scratch
done
cd ..
./waf
cd BIER_code
