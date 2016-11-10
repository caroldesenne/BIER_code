for var in "$@"
do
    cp "$var".cc ../scratch
done

cd ..
./waf

for var in "$@"
do
    ./waf --run scratch/"$var"
done

cd BIER_code
