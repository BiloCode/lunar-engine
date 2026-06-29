#pragma once

#include <Engine/core/vector.h>
#include <Engine/resources/ruby_loader.h>

class r_vector_float
{
public:
   r_vector_float(RubyLoader& ruby);

private:
   RubyLoader& ruby;
};
