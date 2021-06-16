
# pd.pyx
python3 setup.py build_ext --inplace
rm -rf ./build ./pd.c
# python3 -c "import pd"
python3 go.py


# pylibpd.pyx
# python setup.py build_ext --inplace
# rm -rf ./build ./pylibpd.c
# python -c "import pd"
# python go.py

