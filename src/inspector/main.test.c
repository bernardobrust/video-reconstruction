#define ASTF_IMPLEMENTATION
#include <astf.h>

int main() {
    astf_start_test_suite("Tests are working");

    astf_assert_equal(1, 1);

    astf_retrieve_results();

    return 0;
}
