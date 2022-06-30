#!/bin/bash

echo "Generating demo.bin for QSPI Flashing and demo_sim.bin for simulation testing"
mv demo.bin demo_.bin
cat  "../header.bin" "demo_.bin"  >  "demo.bin"
cat  "../header_sim.bin" "demo.bin"  >  "demo_sim.bin"
echo "Done."

echo "Generating c array file for loading the app by an external host over I2C"
cd ../utils/bin2carray/bin/Debug
./bin2carray ../../../../Default/demo.bin
echo "Done. Generated c array file is in cli_test/utils/generated_c_array_file"

echo "Generating interleaved RAM initalization files for simulation testing"
cd ../../../InterleavedRAMFileGen/bin/Debug
./InterleavedRAMFileGen -i ../../../../Default/demo.bin -o 0x800
echo "Done. Generated files are in cli_test/utils/memoryInitFiles"

echo "Generating memory initialization file for simulated flash model"
cd ../../../bin2txt/bin/Debug
./bin2txt ../../../../Default/demo_sim.bin
./bin2txt ../../../../Default/demo.bin
echo "Done. Generated file is in cli_test/utils/memoryInitFiles"
