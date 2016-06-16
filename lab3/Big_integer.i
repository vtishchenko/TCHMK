%module Big_integer
%{
#include "./Big_integer.h"
%}
%rename(_rav) operator =;

%include "./Big_integer.h"
