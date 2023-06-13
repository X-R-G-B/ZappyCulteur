#include <criterion/criterion.h>
#include <criterion/internal/test.h>

#include "circular_buffer.h"

Test(create, creates_a_circular_buffer)
{
    cr_assert_not_null(circular_buffer_create("."));
}

Test(create, creates_a_circular_buffer_with_null_end)
{
    cr_assert_null(circular_buffer_create(NULL));
}
