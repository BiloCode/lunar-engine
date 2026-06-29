#pragma once

#include <Engine/core/vector.h>
#include <Engine/resources/ruby_loader.h>

class r_vector_int
{
public:
   r_vector_int(RubyLoader& ruby);

private:
   RubyLoader& ruby;
};
