DO NOT USE

Please use openssl for production implementations

this is my personal project this currently has several security issues including
but not limited to the following

1. Random numbers are not generated in a cryptographically secure fashion
2. The way keys are check for primaility uses fermates little therom instead of
 the Miller-Rabin test in conjuction with a manual test agianst small values





