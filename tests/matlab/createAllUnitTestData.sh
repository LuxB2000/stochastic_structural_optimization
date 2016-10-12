#!/bin/sh

matlab_exec=matlab
cmd="createAllUnitTestData();exit()"
${matlab_exec} -nojvm -nodisplay -nosplash -r ${cmd}
