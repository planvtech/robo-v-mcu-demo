#!/bin/bash

echo "Generating demo_nexys.bin for QSPI Flashing and demo_nexys_sim.bin for simulation testing"
mv demo.bin demo_nexys_.bin
cat  "../header.bin" "demo_nexys_.bin"  >  "demo_nexys.bin"
cat  "../header_sim.bin" "demo_nexys.bin"  >  "demo_nexys_sim.bin"
echo "Done."

echo "Generating c array file for loading the app by an external host over I2C"
cd ../utils/bin2carray/bin/Debug
./bin2carray ../../../../Default/demo_nexys.bin
echo "Done. Generated c array file is in cli_test/utils/generated_c_array_file"

echo "Generating interleaved RAM initalization files for simulation testing"
cd ../../../InterleavedRAMFileGen/bin/Debug
./InterleavedRAMFileGen -i ../../../../Default/demo_nexys.bin -o 0x800
echo "Done. Generated files are in cli_test/utils/memoryInitFiles"

echo "Generating memory initialization file for simulated flash model"
cd ../../../bin2txt/bin/Debug
./bin2txt ../../../../Default/demo_nexys_sim.bin
./bin2txt ../../../../Default/demo_nexys.bin
echo "Done. Generated file is in cli_test/utils/memoryInitFiles"
