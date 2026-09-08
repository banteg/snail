// Exercise recovered intrusive-list code; fixture storage is not game globals.
#include <stdio.h>
#include <stddef.h>
#include "bod_list.h"

static int checks;
static int failures;
static BodList active;
static BodList other;
static BodNode a, b, c, d;

static void check(bool condition, const char* label)
{
    ++checks;
    if (!condition) {
        ++failures;
        printf("FAIL: %s\n", label);
    }
}

int main(int argc, char** argv)
{
    active.unknown_00 = 0x12345678;
    a.vtable = &a;
    a.list_flags = BOD_FLAG_HAS_OBJECT;
    check(sizeof(BodNode) == 16 && sizeof(BodList) == 12 &&
          offsetof(BodNode, list_prev) == 8 &&
          offsetof(BodNode, list_next) == 12 &&
          offsetof(BodList, first) == 4 && offsetof(BodList, free_top) == 8,
          "native intrusive node and owner boundaries");

    active.add_bod_to_front(&a);
    check(active.first == &a && a.list_prev == 0 && a.list_next == 0,
          "front insertion into empty list");
    check(a.list_flags == (BOD_FLAG_HAS_OBJECT | BOD_FLAG_LINKED),
          "insertion preserves unrelated flags");
    active.add_bod_to_front(&b);
    check(active.first == &b && b.list_prev == 0 && b.list_next == &a &&
          a.list_prev == &b, "front insertion repairs both links");
    active.append_bod_to_end(&c);
    check(a.list_next == &c && c.list_prev == &a && c.list_next == 0 &&
          (c.list_flags & BOD_FLAG_LINKED), "tail insertion walks existing chain");
    active.add_bod_to_front(&a);
    check(active.first == &b && b.list_next == &a && a.list_prev == &b &&
          a.list_next == &c && c.list_prev == &a,
          "duplicate front insertion leaves chain intact");
    active.append_bod_to_end(&a);
    check(active.first == &b && a.list_prev == &b && a.list_next == &c &&
          c.list_next == 0, "duplicate tail insertion leaves chain intact");

    active.recycle_bod_to_free_list(&a);
    check(active.first == &b && b.list_next == &c && c.list_prev == &b,
          "middle removal repairs neighboring links");
    check(active.free_top == &a && a.list_next == 0 &&
          a.list_flags == BOD_FLAG_HAS_OBJECT, "middle removal starts free stack");
    check(a.list_prev == &b, "native removal retains previous-link residue");
    active.recycle_bod_to_free_list(&c);
    check(active.first == &b && b.list_next == 0 && active.free_top == &c &&
          c.list_next == &a && !(c.list_flags & BOD_FLAG_LINKED),
          "tail removal pushes onto existing free stack");
    active.recycle_bod_to_free_list(&b);
    check(active.first == 0 && active.free_top == &b && b.list_next == &c &&
          c.list_next == &a && !(b.list_flags & BOD_FLAG_LINKED),
          "head removal empties active list and preserves free order");
    active.recycle_bod_to_free_list(&b);
    check(active.first == 0 && active.free_top == &b && b.list_next == &c &&
          c.list_next == &a, "unlinked removal is rejected without mutation");

    // Taking a node from free_top is fixture setup. This group does not claim
    // to recover a pool allocator or a complete constructor/destructor cycle.
    active.free_top = b.list_next;
    active.append_bod_to_end(&b);
    check(active.first == &b && b.list_prev == 0 && b.list_next == 0 &&
          active.free_top == &c, "empty tail insertion reuses a detached node");
    b.list_flags |= BOD_FLAG_NEXT_UPDATE_GUARD;
    active.recycle_bod_to_free_list(&b);
    check(active.first == &b && b.list_prev == 0 && b.list_next == 0 &&
          active.free_top == &c &&
          b.list_flags == (BOD_FLAG_LINKED | BOD_FLAG_NEXT_UPDATE_GUARD),
          "saved-next guard rejects active node removal");
    b.list_flags &= ~BOD_FLAG_NEXT_UPDATE_GUARD;
    active.recycle_bod_to_free_list(&b);
    check(active.first == 0 && active.free_top == &b && b.list_next == &c &&
          !(b.list_flags & BOD_FLAG_LINKED), "clearing saved-next guard permits removal");

    other.append_bod_to_end(&d);
    check(other.first == &d && d.list_prev == 0 && d.list_next == 0 &&
          other.free_top == 0, "second owner receives its own active node");
    other.recycle_bod_to_free_list(&d);
    check(other.first == 0 && other.free_top == &d && d.list_next == 0,
          "second owner receives its own recycled node");
    check(active.first == 0 && active.free_top == &b && b.list_next == &c &&
          c.list_next == &a, "owners retain independent free stacks");
    check(active.unknown_00 == 0x12345678 && a.vtable == &a,
          "list operations preserve unowned header and callback fields");
    if (argc == 2 && argv[1][0] == '!')
        c.list_next = 0;
    check(active.free_top == &b && b.list_next == &c && c.list_next == &a &&
          a.list_next == 0, "complete final free chain");

    printf("bod-list checks=%d failures=%d\n", checks, failures);
    fflush(0);
    return failures ? 1 : 0;
}
