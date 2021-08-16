mkdir Build
cd Build
g++ -I ../Source -I /opt/devkitpro/libogc/include/ -c $(find ../Source -name '*.cpp') -std=c++17 -fpermissive $1
g++ -I ../Source $(find . -name '*.o') -o app $1
cd ..