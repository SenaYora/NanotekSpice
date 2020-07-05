/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** test_bestfit
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "UserInput.hpp"
#include "True.hpp"
#include "False.hpp"
#include "Clock.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "FlipFlop.hpp"
#include "C_4001.hpp"
#include "C_4008.hpp"
#include "C_4011.hpp"
#include "C_4013.hpp"
#include "C_4017.hpp"
#include "C_4030.hpp"
#include "C_4040.hpp"
#include "C_4069.hpp"
#include "C_4071.hpp"
#include "C_4081.hpp"
#include "C_4514.hpp"

void redirect_all_std(void){
    cr_redirect_stderr();
    cr_redirect_stdout();
    cr_redirect_stdin();
}

Test(input, test_input, .init = redirect_all_std)
{
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::TRUE);
    cr_assert_eq(i->compute(), 1);
}

Test(input, test_input2, .init = redirect_all_std)
{
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::FALSE);
    cr_assert_eq(i->compute(), 0);
}

Test(input, test_input3, .init = redirect_all_std)
{
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::UNDEFINED);
    cr_assert_eq(i->compute(), -1);
}

Test(input, test_input4, .init = redirect_all_std)
{
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->dump();
    cr_assert_eq(i->getName(), "yes");
}

/*
** OUTPUT
*/

Test(output, test_output, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");

    s->dump();
    cr_assert_eq(s->getName(), "no");
}

/*
** LINK
*/

Test(link, test_link, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::FALSE);
    s->setLink(1, *(i.get()), 1);
    i->setLink(1, *(s.get()), 1);
    cr_assert_eq(s->compute(), 0);
}

Test(link, test_link2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::TRUE);
    s->setLink(1, *(i.get()), 1);
    i->setLink(1, *(s.get()), 1);
    cr_assert_eq(s->compute(), 1);
}

Test(link, test_link3, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::TRUE);
    try {
        i->setLink(2, *(s.get()), 1);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "pin '2' doesn't exist on Input component");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(link, test_link4, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::TRUE);
    try {
        s->setLink(2, *(i.get()), 1);
    } catch (Errors const &e) {
        cr_assert_null(NULL);
        return;
    }
    cr_assert_not_null(NULL);
}

Test(link, test_link5, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::TRUE);
    try {
        s->compute();
    } catch (Errors const &e) {
        cr_assert_null(NULL);
        return;
    }
    cr_assert_not_null(NULL);
}

Test(link, test_link6, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");
    std::unique_ptr<Input> i = std::make_unique<Input>("yes");

    i->setValue(nts::TRUE);
    s->setLink(1, *(i.get()), 1);
    cr_assert_eq(s->compute(2), nts::FALSE);
}

/*
** TRUE & FALSE
*/

Test(TRUE, test_true, .init = redirect_all_std)
{
    std::unique_ptr<True> t = std::make_unique<True>("true");

    t->dump();
    cr_assert_eq(t->getName(), "true");
    try {
        t->setValue(nts::FALSE);
    } catch (Errors const &e) {
        cr_assert_eq(t->compute(), 1);
        return;
    }
    cr_assert_not_null(NULL);
}

Test(FALSE, test_false, .init = redirect_all_std)
{
    std::unique_ptr<False> t = std::make_unique<False>("false");

    t->dump();
    cr_assert_eq(t->getName(), "false");
    try {
        t->setValue(nts::TRUE);
    } catch (Errors const &e) {
        cr_assert_eq(t->compute(), 0);
        return;
    }
    cr_assert_not_null(NULL);
}

Test(TRUE, test_true2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");
    std::unique_ptr<True> i = std::make_unique<True>("true");

    s->setLink(1, *(i.get()), 1);
    i->setLink(1, *(s.get()), 1);
    cr_assert_eq(s->compute(), nts::TRUE);
}

Test(FALSE, test_false2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("no");
    std::unique_ptr<False> i = std::make_unique<False>("true");

    s->setLink(1, *(i.get()), 1);
    i->setLink(1, *(s.get()), 1);
    cr_assert_eq(s->compute(), nts::FALSE);
}

/*
** C_4001
*/

Test(C_4001, test_4001, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4001, test_4001_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4001, test_4001_3, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4001, test_4001_4, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4001, test_4001_5, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4001, test_4001_6, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4001, test_4001_7, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4001, test_4001_8, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4001, test_4001_9, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4001, test_4001_10, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4001> gate = std::make_unique<C_4001>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
    a->setValue(nts::TRUE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(5, *(a.get()), 1);
    gate->setLink(6, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 4);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(8, *(a.get()), 1);
    gate->setLink(9, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 10);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(13, *(a.get()), 1);
    gate->setLink(12, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 11);
    cr_assert_eq(s->compute(), 0);

    cr_assert_eq(gate->compute(2), 0);
}

/*
** C_4008
*/

Test(C_4008, test_4008, .init = redirect_all_std)
{
    std::unique_ptr<C_4008> gate = std::make_unique<C_4008>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
}

Test(C_4008, test_4008_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> o1 = std::make_unique<Output>("output");
    std::unique_ptr<Output> o2 = std::make_unique<Output>("output2");
    std::unique_ptr<Output> o3 = std::make_unique<Output>("output3");
    std::unique_ptr<Output> o4 = std::make_unique<Output>("output4");
    std::unique_ptr<Output> cout = std::make_unique<Output>("output5");
    std::unique_ptr<Input> a1 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> a2 = std::make_unique<Input>("input2");
    std::unique_ptr<Input> a3 = std::make_unique<Input>("input3");
    std::unique_ptr<Input> a4 = std::make_unique<Input>("input4");
    std::unique_ptr<Input> b1 = std::make_unique<Input>("input5");
    std::unique_ptr<Input> b2 = std::make_unique<Input>("input6");
    std::unique_ptr<Input> b3 = std::make_unique<Input>("input7");
    std::unique_ptr<Input> b4 = std::make_unique<Input>("input8");
    std::unique_ptr<Input> cin = std::make_unique<Input>("input9");
    std::unique_ptr<C_4008> gate = std::make_unique<C_4008>("4001");

    a1->setValue(nts::FALSE);
    a2->setValue(nts::FALSE);
    a3->setValue(nts::FALSE);
    a4->setValue(nts::FALSE);
    b1->setValue(nts::FALSE);
    b2->setValue(nts::FALSE);
    b3->setValue(nts::FALSE);
    b4->setValue(nts::FALSE);
    cin->setValue(nts::FALSE);

    gate->setLink(7, *(a1.get()), 1);
    gate->setLink(5, *(a2.get()), 1);
    gate->setLink(3, *(a3.get()), 1);
    gate->setLink(1, *(a4.get()), 1);
    gate->setLink(7 - 1, *(b1.get()), 1);
    gate->setLink(5 - 1, *(b2.get()), 1);
    gate->setLink(3 - 1, *(b3.get()), 1);
    gate->setLink(15, *(b4.get()), 1);
    gate->setLink(9, *(cin.get()), 1);

    o1->setLink(1, *(gate.get()), 10);
    o2->setLink(1, *(gate.get()), 11);
    o3->setLink(1, *(gate.get()), 12);
    o4->setLink(1, *(gate.get()), 13);
    cout->setLink(1, *(gate.get()), 14);
    cr_assert_eq(gate->compute(10), 0);
    cr_assert_eq(gate->compute(11), 0);
    cr_assert_eq(gate->compute(12), 0);
    cr_assert_eq(gate->compute(13), 0);
    cr_assert_eq(gate->compute(14), 0);
    cr_assert_eq(gate->compute(1), 0);
}

/*
** C_4011
*/

Test(C_4011, test_4011, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4011, test_4011_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4011, test_4011_3, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4011, test_4011_4, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4011, test_4011_5, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4011, test_4011_6, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4011, test_4011_7, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4011, test_4011_8, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4011, test_4011_9, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4011, test_4011_10, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4011> gate = std::make_unique<C_4011>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
    a->setValue(nts::TRUE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(5, *(a.get()), 1);
    gate->setLink(6, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 4);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(8, *(a.get()), 1);
    gate->setLink(9, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 10);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(13, *(a.get()), 1);
    gate->setLink(12, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 11);
    cr_assert_eq(s->compute(), 0);

    cr_assert_eq(gate->compute(2), 0);
}

/*
** C_4013
*/

Test(C_4013, test_4013, .init = redirect_all_std)
{
    std::unique_ptr<FlipFlop> fp = std::make_unique<FlipFlop>("oui");
    std::unique_ptr<C_4013> gate = std::make_unique<C_4013>("4001");

    fp->setLink(0, *(gate.get()), 0);
    fp->dump();
    fp->getName();
    fp->setValue(nts::UNDEFINED);

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
}

Test(C_4013, test_4013_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> q1 = std::make_unique<Output>("Q1");
    std::unique_ptr<Output> q1n = std::make_unique<Output>("Q1NOT");
    std::unique_ptr<Output> q2 = std::make_unique<Output>("Q2");
    std::unique_ptr<Output> q2n = std::make_unique<Output>("Q2NOT");
    std::unique_ptr<Input> data1 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> data2 = std::make_unique<Input>("input2");
    std::unique_ptr<Clock> clock1 = std::make_unique<Clock>("input3");
    std::unique_ptr<Clock> clock2 = std::make_unique<Clock>("input3");
    std::unique_ptr<Input> set1 = std::make_unique<Input>("input5");
    std::unique_ptr<Input> set2 = std::make_unique<Input>("input6");
    std::unique_ptr<Input> reset1 = std::make_unique<Input>("input7");
    std::unique_ptr<Input> reset2 = std::make_unique<Input>("input8");
    std::unique_ptr<C_4013> gate = std::make_unique<C_4013>("4001");

    data1->setValue(nts::FALSE);
    data2->setValue(nts::FALSE);
    clock1->setValue(nts::FALSE);
    clock2->setValue(nts::FALSE);
    set1->setValue(nts::FALSE);
    set2->setValue(nts::FALSE);
    reset1->setValue(nts::FALSE);
    reset2->setValue(nts::FALSE);

    gate->setLink(3, *(clock1.get()), 1);
    gate->setLink(4, *(reset1.get()), 1);
    gate->setLink(5, *(data1.get()), 1);
    gate->setLink(6, *(set1.get()), 1);
    gate->setLink(8, *(set2.get()), 1);
    gate->setLink(9, *(data2.get()), 1);
    gate->setLink(10, *(reset2.get()), 1);
    gate->setLink(11, *(clock2.get()), 1);

    q1->setLink(1, *(gate.get()), 1);
    q1n->setLink(1, *(gate.get()), 2);
    q2->setLink(1, *(gate.get()), 13);
    q2n->setLink(1, *(gate.get()), 12);

    cr_assert_eq(q1->compute(), 0);
    cr_assert_eq(q1n->compute(), 1);
    cr_assert_eq(q2->compute(), 0);
    cr_assert_eq(q2n->compute(), 1);
}

Test(C_4013, test_4013_3, .init = redirect_all_std)
{
    std::unique_ptr<Output> q1 = std::make_unique<Output>("Q1");
    std::unique_ptr<Output> q1n = std::make_unique<Output>("Q1NOT");
    std::unique_ptr<Output> q2 = std::make_unique<Output>("Q2");
    std::unique_ptr<Output> q2n = std::make_unique<Output>("Q2NOT");
    std::unique_ptr<Input> data1 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> data2 = std::make_unique<Input>("input2");
    std::unique_ptr<Clock> clock1 = std::make_unique<Clock>("input3");
    std::unique_ptr<Clock> clock2 = std::make_unique<Clock>("input3");
    std::unique_ptr<Input> set1 = std::make_unique<Input>("input5");
    std::unique_ptr<Input> set2 = std::make_unique<Input>("input6");
    std::unique_ptr<Input> reset1 = std::make_unique<Input>("input7");
    std::unique_ptr<Input> reset2 = std::make_unique<Input>("input8");
    std::unique_ptr<C_4013> gate = std::make_unique<C_4013>("4001");

    data1->setValue(nts::FALSE);
    data2->setValue(nts::FALSE);
    clock1->setValue(nts::TRUE);
    clock2->setValue(nts::TRUE);
    set1->setValue(nts::FALSE);
    set2->setValue(nts::FALSE);
    reset1->setValue(nts::FALSE);
    reset2->setValue(nts::FALSE);

    gate->setLink(3, *(clock1.get()), 1);
    gate->setLink(4, *(reset1.get()), 1);
    gate->setLink(5, *(data1.get()), 1);
    gate->setLink(6, *(set1.get()), 1);
    gate->setLink(8, *(set2.get()), 1);
    gate->setLink(9, *(data2.get()), 1);
    gate->setLink(10, *(reset2.get()), 1);
    gate->setLink(11, *(clock2.get()), 1);

    q1->setLink(1, *(gate.get()), 1);
    q1n->setLink(1, *(gate.get()), 2);
    q2->setLink(1, *(gate.get()), 13);
    q2n->setLink(1, *(gate.get()), 12);

    cr_assert_eq(q1->compute(), 0);
    cr_assert_eq(q1n->compute(), 1);
    cr_assert_eq(q2->compute(), 0);
    cr_assert_eq(q2n->compute(), 1);
}

Test(C_4013, test_4013_4, .init = redirect_all_std)
{
    std::unique_ptr<Output> q1 = std::make_unique<Output>("Q1");
    std::unique_ptr<Output> q1n = std::make_unique<Output>("Q1NOT");
    std::unique_ptr<Output> q2 = std::make_unique<Output>("Q2");
    std::unique_ptr<Output> q2n = std::make_unique<Output>("Q2NOT");
    std::unique_ptr<Input> data1 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> data2 = std::make_unique<Input>("input2");
    std::unique_ptr<Clock> clock1 = std::make_unique<Clock>("input3");
    std::unique_ptr<Clock> clock2 = std::make_unique<Clock>("input3");
    std::unique_ptr<Input> set1 = std::make_unique<Input>("input5");
    std::unique_ptr<Input> set2 = std::make_unique<Input>("input6");
    std::unique_ptr<Input> reset1 = std::make_unique<Input>("input7");
    std::unique_ptr<Input> reset2 = std::make_unique<Input>("input8");
    std::unique_ptr<C_4013> gate = std::make_unique<C_4013>("4001");

    data1->setValue(nts::FALSE);
    data2->setValue(nts::FALSE);
    clock1->setValue(nts::FALSE);
    clock2->setValue(nts::FALSE);
    set1->setValue(nts::FALSE);
    set2->setValue(nts::FALSE);
    reset1->setValue(nts::TRUE);
    reset2->setValue(nts::TRUE);

    gate->setLink(3, *(clock1.get()), 1);
    gate->setLink(4, *(reset1.get()), 1);
    gate->setLink(5, *(data1.get()), 1);
    gate->setLink(6, *(set1.get()), 1);
    gate->setLink(8, *(set2.get()), 1);
    gate->setLink(9, *(data2.get()), 1);
    gate->setLink(10, *(reset2.get()), 1);
    gate->setLink(11, *(clock2.get()), 1);

    q1->setLink(1, *(gate.get()), 1);
    q1n->setLink(1, *(gate.get()), 2);
    q2->setLink(1, *(gate.get()), 13);
    q2n->setLink(1, *(gate.get()), 12);

    cr_assert_eq(q1->compute(), 0);
    cr_assert_eq(q1n->compute(), 1);
    cr_assert_eq(q2->compute(), 0);
    cr_assert_eq(q2n->compute(), 1);
    cr_assert_eq(gate->compute(0), 0);
}

Test(C_4013, test_4013_5, .init = redirect_all_std)
{
    std::unique_ptr<Output> q1 = std::make_unique<Output>("Q1");
    std::unique_ptr<Output> q1n = std::make_unique<Output>("Q1NOT");
    std::unique_ptr<Output> q2 = std::make_unique<Output>("Q2");
    std::unique_ptr<Output> q2n = std::make_unique<Output>("Q2NOT");
    std::unique_ptr<Input> data1 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> data2 = std::make_unique<Input>("input2");
    std::unique_ptr<Clock> clock1 = std::make_unique<Clock>("input3");
    std::unique_ptr<Clock> clock2 = std::make_unique<Clock>("input3");
    std::unique_ptr<Input> set1 = std::make_unique<Input>("input5");
    std::unique_ptr<Input> set2 = std::make_unique<Input>("input6");
    std::unique_ptr<Input> reset1 = std::make_unique<Input>("input7");
    std::unique_ptr<Input> reset2 = std::make_unique<Input>("input8");
    std::unique_ptr<C_4013> gate = std::make_unique<C_4013>("4001");

    data1->setValue(nts::FALSE);
    data2->setValue(nts::FALSE);
    clock1->setValue(nts::FALSE);
    clock2->setValue(nts::FALSE);
    set1->setValue(nts::TRUE);
    set2->setValue(nts::TRUE);
    reset1->setValue(nts::TRUE);
    reset2->setValue(nts::TRUE);

    gate->setLink(3, *(clock1.get()), 1);
    gate->setLink(4, *(reset1.get()), 1);
    gate->setLink(5, *(data1.get()), 1);
    gate->setLink(6, *(set1.get()), 1);
    gate->setLink(8, *(set2.get()), 1);
    gate->setLink(9, *(data2.get()), 1);
    gate->setLink(10, *(reset2.get()), 1);
    gate->setLink(11, *(clock2.get()), 1);

    q1->setLink(1, *(gate.get()), 1);
    q1n->setLink(1, *(gate.get()), 2);
    q2->setLink(1, *(gate.get()), 13);
    q2n->setLink(1, *(gate.get()), 12);

    cr_assert_eq(q1->compute(), 1);
    cr_assert_eq(q1n->compute(), 1);
    cr_assert_eq(q2->compute(), 1);
    cr_assert_eq(q2n->compute(), 1);
}

Test(C_4013, test_4013_6, .init = redirect_all_std)
{
    std::unique_ptr<Output> q1 = std::make_unique<Output>("Q1");
    std::unique_ptr<Output> q1n = std::make_unique<Output>("Q1NOT");
    std::unique_ptr<Output> q2 = std::make_unique<Output>("Q2");
    std::unique_ptr<Output> q2n = std::make_unique<Output>("Q2NOT");
    std::unique_ptr<Input> data1 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> data2 = std::make_unique<Input>("input2");
    std::unique_ptr<Clock> clock1 = std::make_unique<Clock>("input3");
    std::unique_ptr<Clock> clock2 = std::make_unique<Clock>("input3");
    std::unique_ptr<Input> set1 = std::make_unique<Input>("input5");
    std::unique_ptr<Input> set2 = std::make_unique<Input>("input6");
    std::unique_ptr<Input> reset1 = std::make_unique<Input>("input7");
    std::unique_ptr<Input> reset2 = std::make_unique<Input>("input8");
    std::unique_ptr<C_4013> gate = std::make_unique<C_4013>("4001");

    data1->setValue(nts::FALSE);
    data2->setValue(nts::TRUE);
    clock1->setValue(nts::TRUE);
    clock2->setValue(nts::TRUE);
    set1->setValue(nts::FALSE);
    set2->setValue(nts::FALSE);
    reset1->setValue(nts::FALSE);
    reset2->setValue(nts::FALSE);

    gate->setLink(3, *(clock1.get()), 1);
    gate->setLink(4, *(reset1.get()), 1);
    gate->setLink(5, *(data1.get()), 1);
    gate->setLink(6, *(set1.get()), 1);
    gate->setLink(8, *(set2.get()), 1);
    gate->setLink(9, *(data2.get()), 1);
    gate->setLink(10, *(reset2.get()), 1);
    gate->setLink(11, *(clock2.get()), 1);

    q1->setLink(1, *(gate.get()), 1);
    q1n->setLink(1, *(gate.get()), 2);
    q2->setLink(1, *(gate.get()), 13);
    q2n->setLink(1, *(gate.get()), 12);

    cr_assert_eq(q1->compute(), 0);
    cr_assert_eq(q1n->compute(), 1);
    cr_assert_eq(q2->compute(), 1);
    cr_assert_eq(q2n->compute(), 0);
}

/*
** C_4017
*/

Test(C_4017, test_4017, .init = redirect_all_std)
{
    std::unique_ptr<C_4017> gate = std::make_unique<C_4017>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
}

Test(C_4017, test_4017_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> o0 = std::make_unique<Output>("o0");
    std::unique_ptr<Output> o1 = std::make_unique<Output>("o1");
    std::unique_ptr<Output> o2 = std::make_unique<Output>("o2");
    std::unique_ptr<Output> o3 = std::make_unique<Output>("o3");
    std::unique_ptr<Output> o4 = std::make_unique<Output>("o4");
    std::unique_ptr<Output> o5 = std::make_unique<Output>("o5");
    std::unique_ptr<Output> o6 = std::make_unique<Output>("o6");
    std::unique_ptr<Output> o7 = std::make_unique<Output>("o7");
    std::unique_ptr<Output> o8 = std::make_unique<Output>("o8");
    std::unique_ptr<Output> o9 = std::make_unique<Output>("o9");
    std::unique_ptr<Output> c = std::make_unique<Output>("c");
    std::unique_ptr<Clock> clock = std::make_unique<Clock>("clock");
    std::unique_ptr<Input> reset = std::make_unique<Input>("reset");
    std::unique_ptr<C_4017> gate = std::make_unique<C_4017>("4001");

    clock->setValue(nts::FALSE);
    reset->setValue(nts::FALSE);

    gate->setLink(14, *(clock.get()), 1);
    gate->setLink(15, *(reset.get()), 1);
    gate->setLink(12, *(c.get()), 1);

    o0->setLink(1, *(gate.get()), 3);
    o1->setLink(1, *(gate.get()), 2);
    o2->setLink(1, *(gate.get()), 4);
    o3->setLink(1, *(gate.get()), 7);
    o4->setLink(1, *(gate.get()), 10);
    o5->setLink(1, *(gate.get()), 1);
    o6->setLink(1, *(gate.get()), 5);
    o7->setLink(1, *(gate.get()), 6);
    o8->setLink(1, *(gate.get()), 9);
    o9->setLink(1, *(gate.get()), 11);
    c->setLink(1, *(gate.get()), 12);

    cr_assert_eq(o0->compute(), 1);
    cr_assert_eq(o1->compute(), 0);
    cr_assert_eq(o2->compute(), 0);
    cr_assert_eq(o3->compute(), 0);
    cr_assert_eq(o4->compute(), 0);
    cr_assert_eq(o5->compute(), 0);
    cr_assert_eq(o6->compute(), 0);
    cr_assert_eq(o7->compute(), 0);
    cr_assert_eq(o8->compute(), 0);
    cr_assert_eq(o9->compute(), 0);
    cr_assert_eq(c->compute(), 1);

    clock->setValue(nts::TRUE);
    cr_assert_eq(o0->compute(), 0);
    cr_assert_eq(o1->compute(), 1);
    cr_assert_eq(o2->compute(), 0);
    cr_assert_eq(o3->compute(), 0);
    cr_assert_eq(o4->compute(), 0);
    cr_assert_eq(o5->compute(), 0);
    cr_assert_eq(o6->compute(), 0);
    cr_assert_eq(o7->compute(), 0);
    cr_assert_eq(o8->compute(), 0);
    cr_assert_eq(o9->compute(), 0);
    cr_assert_eq(c->compute(), 1);

    cr_assert_eq(o0->compute(), 0);
    cr_assert_eq(o1->compute(), 0);
    cr_assert_eq(o2->compute(), 1);
    cr_assert_eq(o3->compute(), 0);
    cr_assert_eq(o4->compute(), 0);
    cr_assert_eq(o5->compute(), 0);
    cr_assert_eq(o6->compute(), 0);
    cr_assert_eq(o7->compute(), 0);
    cr_assert_eq(o8->compute(), 0);
    cr_assert_eq(o9->compute(), 0);
    cr_assert_eq(c->compute(), 1);

    cr_assert_eq(o0->compute(), 0);
    cr_assert_eq(o1->compute(), 0);
    cr_assert_eq(o2->compute(), 0);
    cr_assert_eq(o3->compute(), 1);
    cr_assert_eq(o4->compute(), 0);
    cr_assert_eq(o5->compute(), 0);
    cr_assert_eq(o6->compute(), 0);
    cr_assert_eq(o7->compute(), 0);
    cr_assert_eq(o8->compute(), 0);
    cr_assert_eq(o9->compute(), 0);
    cr_assert_eq(c->compute(), 1);

    cr_assert_eq(o0->compute(), 0);
    cr_assert_eq(o1->compute(), 0);
    cr_assert_eq(o2->compute(), 0);
    cr_assert_eq(o3->compute(), 0);
    cr_assert_eq(o4->compute(), 1);
    cr_assert_eq(o5->compute(), 0);
    cr_assert_eq(o6->compute(), 0);
    cr_assert_eq(o7->compute(), 0);
    cr_assert_eq(o8->compute(), 0);
    cr_assert_eq(o9->compute(), 0);
    cr_assert_eq(c->compute(), 1);

    cr_assert_eq(o0->compute(), 0);
    cr_assert_eq(o1->compute(), 0);
    cr_assert_eq(o2->compute(), 0);
    cr_assert_eq(o3->compute(), 0);
    cr_assert_eq(o4->compute(), 0);
    cr_assert_eq(o5->compute(), 1);
    cr_assert_eq(o6->compute(), 0);
    cr_assert_eq(o7->compute(), 0);
    cr_assert_eq(o8->compute(), 0);
    cr_assert_eq(o9->compute(), 0);
    cr_assert_eq(c->compute(), 0);

    reset->setValue(nts::TRUE);
    cr_assert_eq(o0->compute(), 1);
    cr_assert_eq(o1->compute(), 0);
    cr_assert_eq(o2->compute(), 0);
    cr_assert_eq(o3->compute(), 0);
    cr_assert_eq(o4->compute(), 0);
    cr_assert_eq(o5->compute(), 0);
    cr_assert_eq(o6->compute(), 0);
    cr_assert_eq(o7->compute(), 0);
    cr_assert_eq(o8->compute(), 0);
    cr_assert_eq(o9->compute(), 0);
    cr_assert_eq(c->compute(), 1);

    cr_assert_eq(gate->compute(0), 0);
}

/*
** C_4030
*/

Test(C_4030, test_4030, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4030, test_4030_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4030, test_4030_3, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4030, test_4030_4, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4030, test_4030_5, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4030, test_4030_6, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4030, test_4030_7, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4030, test_4030_8, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4030, test_4030_9, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4030, test_4030_10, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4030> gate = std::make_unique<C_4030>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
    a->setValue(nts::TRUE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(5, *(a.get()), 1);
    gate->setLink(6, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 4);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(8, *(a.get()), 1);
    gate->setLink(9, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 10);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(13, *(a.get()), 1);
    gate->setLink(12, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 11);
    cr_assert_eq(s->compute(), 0);

    cr_assert_eq(gate->compute(2), 0);
}

/*
** C_4040
*/

Test(C_4040, test_4040, .init = redirect_all_std)
{
    std::unique_ptr<C_4040> gate = std::make_unique<C_4040>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
}

Test(C_4040, test_4040_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> o0 = std::make_unique<Output>("o0");
    std::unique_ptr<Output> o1 = std::make_unique<Output>("o1");
    std::unique_ptr<Output> o2 = std::make_unique<Output>("o2");
    std::unique_ptr<Output> o3 = std::make_unique<Output>("o3");
    std::unique_ptr<Output> o4 = std::make_unique<Output>("o4");
    std::unique_ptr<Output> o5 = std::make_unique<Output>("o5");
    std::unique_ptr<Output> o6 = std::make_unique<Output>("o6");
    std::unique_ptr<Output> o7 = std::make_unique<Output>("o7");
    std::unique_ptr<Output> o8 = std::make_unique<Output>("o8");
    std::unique_ptr<Output> o9 = std::make_unique<Output>("o9");
    std::unique_ptr<Output> o10 = std::make_unique<Output>("o10");
    std::unique_ptr<Output> o11 = std::make_unique<Output>("o11");
    std::unique_ptr<Clock> clock = std::make_unique<Clock>("clock");
    std::unique_ptr<Input> reset = std::make_unique<Input>("reset");
    std::unique_ptr<C_4040> gate = std::make_unique<C_4040>("4001");

    nts::Tristate expected[12] = {
        nts::FALSE, nts::FALSE, nts::FALSE, nts::FALSE,
        nts::FALSE, nts::FALSE, nts::FALSE, nts::FALSE,
        nts::FALSE, nts::FALSE, nts::FALSE, nts::FALSE
    };

    clock->setValue(nts::TRUE);
    reset->setValue(nts::FALSE);

    gate->setLink(10, *(clock.get()), 1);
    gate->setLink(11, *(reset.get()), 1);

    o0->setLink(1, *(gate.get()), 9);
    o1->setLink(1, *(gate.get()), 7);
    o2->setLink(1, *(gate.get()), 6);
    o3->setLink(1, *(gate.get()), 5);
    o4->setLink(1, *(gate.get()), 3);
    o5->setLink(1, *(gate.get()), 2);
    o6->setLink(1, *(gate.get()), 4);
    o7->setLink(1, *(gate.get()), 13);
    o8->setLink(1, *(gate.get()), 12);
    o9->setLink(1, *(gate.get()), 14);
    o10->setLink(1, *(gate.get()), 15);
    o11->setLink(1, *(gate.get()), 1);

    for (std::size_t counter = 0; counter < 10000; counter++) {
        std::size_t bit_num = 11;
        for (std::size_t i = 1u << (12 - 1); i; i >>= 1, bit_num -= 1)
            expected[bit_num] = static_cast<nts::Tristate>(counter & i ? 1 : 0);
        cr_assert_eq(o0->compute(), expected[0]);
        cr_assert_eq(o1->compute(), expected[1]);
        cr_assert_eq(o2->compute(), expected[2]);
        cr_assert_eq(o3->compute(), expected[3]);
        cr_assert_eq(o4->compute(), expected[4]);
        cr_assert_eq(o5->compute(), expected[5]);
        cr_assert_eq(o6->compute(), expected[6]);
        cr_assert_eq(o7->compute(), expected[7]);
        cr_assert_eq(o8->compute(), expected[8]);
        cr_assert_eq(o9->compute(), expected[9]);
        cr_assert_eq(o10->compute(), expected[10]);
        cr_assert_eq(o11->compute(), expected[11]);
        clock->setValue(nts::FALSE);
    }
    reset->setValue(nts::TRUE);
    cr_assert_eq(o0->compute(), 0);
    cr_assert_eq(o1->compute(), 0);
    cr_assert_eq(o2->compute(), 0);
    cr_assert_eq(o3->compute(), 0);
    cr_assert_eq(o4->compute(), 0);
    cr_assert_eq(o5->compute(), 0);
    cr_assert_eq(o6->compute(), 0);
    cr_assert_eq(o7->compute(), 0);
    cr_assert_eq(o8->compute(), 0);
    cr_assert_eq(o9->compute(), 0);
    cr_assert_eq(o10->compute(), 0);
    cr_assert_eq(o11->compute(), 0);
    cr_assert_eq(gate->compute(0), 0);
}

/*
** C_4069
*/

Test(C_4069, test_4069, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<C_4069> gate = std::make_unique<C_4069>("4001");

    a->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 2);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4069, test_4069_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<C_4069> gate = std::make_unique<C_4069>("4001");

    a->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 2);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4069, test_4069_3, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<C_4069> gate = std::make_unique<C_4069>("4001");

    a->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 2);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4069, test_4069_4, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4069> gate = std::make_unique<C_4069>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
    a->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 2);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(3, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 4);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(5, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 6);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(9, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 8);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(11, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 10);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(13, *(a.get()), 1);
    s->setLink(1, *(gate.get()), 12);
    cr_assert_eq(s->compute(), 0);

    cr_assert_eq(gate->compute(15), 0);
}

/*
** C_4071
*/

Test(C_4071, test_4071, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4071, test_4071_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4071, test_4071_3, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4071, test_4071_4, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4071, test_4071_5, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4071, test_4071_6, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4071, test_4071_7, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4071, test_4071_8, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4071, test_4071_9, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4071, test_4071_10, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4071> gate = std::make_unique<C_4071>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
    a->setValue(nts::FALSE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(5, *(a.get()), 1);
    gate->setLink(6, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 4);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(8, *(a.get()), 1);
    gate->setLink(9, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 10);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(13, *(a.get()), 1);
    gate->setLink(12, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 11);
    cr_assert_eq(s->compute(), 0);

    cr_assert_eq(gate->compute(2), 0);
}

/*
** C_4081
*/

Test(C_4081, test_4081, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 1);
}

Test(C_4081, test_4081_2, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4081, test_4081_3, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4081, test_4081_4, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4081, test_4081_5, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4081, test_4081_6, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::FALSE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4081, test_4081_7, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);
}

Test(C_4081, test_4081_8, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::UNDEFINED);
    b->setValue(nts::TRUE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4081, test_4081_9, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    a->setValue(nts::TRUE);
    b->setValue(nts::UNDEFINED);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), -1);
}

Test(C_4081, test_4081_10, .init = redirect_all_std)
{
    std::unique_ptr<Output> s = std::make_unique<Output>("output");
    std::unique_ptr<Input> a = std::make_unique<Input>("input1");
    std::unique_ptr<Input> b = std::make_unique<Input>("input2");
    std::unique_ptr<C_4081> gate = std::make_unique<C_4081>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
    a->setValue(nts::FALSE);
    b->setValue(nts::FALSE);
    gate->setLink(1, *(a.get()), 1);
    gate->setLink(2, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 3);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(5, *(a.get()), 1);
    gate->setLink(6, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 4);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(8, *(a.get()), 1);
    gate->setLink(9, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 10);
    cr_assert_eq(s->compute(), 0);

    gate->setLink(13, *(a.get()), 1);
    gate->setLink(12, *(b.get()), 1);
    s->setLink(1, *(gate.get()), 11);
    cr_assert_eq(s->compute(), 0);

    cr_assert_eq(gate->compute(2), 0);
}

/*
** C_4514
*/

Test(C_4514, test_4514, .init = redirect_all_std)
{
    std::unique_ptr<C_4514> gate = std::make_unique<C_4514>("4001");

    gate->dump();
    cr_assert_eq(gate->getName(), "4001");
}

Test(C_4514, test_4514_2)
{
    std::unique_ptr<Output> s0 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s1 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s2 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s3 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s4 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s5 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s6 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s7 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s8 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s9 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s10 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s11 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s12 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s13 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s14 = std::make_unique<Output>("output");
    std::unique_ptr<Output> s15 = std::make_unique<Output>("output");
    std::unique_ptr<Input> a0 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> a1 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> a2 = std::make_unique<Input>("input1");
    std::unique_ptr<Input> a3 = std::make_unique<Input>("input2");
    std::unique_ptr<Input> strobe = std::make_unique<Input>("input2");
    std::unique_ptr<Input> i = std::make_unique<Input>("input2");
    std::unique_ptr<C_4514> gate = std::make_unique<C_4514>("4001");

    a0->setValue(nts::FALSE);
    a1->setValue(nts::FALSE);
    a2->setValue(nts::FALSE);
    a3->setValue(nts::FALSE);

    gate->setLink(2, *(a0.get()), 1);
    gate->setLink(3, *(a1.get()), 1);
    gate->setLink(21, *(a2.get()), 1);
    gate->setLink(22, *(a3.get()), 1);

    s0->setLink(1, *(gate.get()), 11);
    s1->setLink(1, *(gate.get()), 9);
    s2->setLink(1, *(gate.get()), 10);
    s3->setLink(1, *(gate.get()), 8);
    s4->setLink(1, *(gate.get()), 7);
    s5->setLink(1, *(gate.get()), 6);
    s6->setLink(1, *(gate.get()), 5);
    s7->setLink(1, *(gate.get()), 4);
    s8->setLink(1, *(gate.get()), 18);
    s9->setLink(1, *(gate.get()), 17);
    s10->setLink(1, *(gate.get()), 20);
    s11->setLink(1, *(gate.get()), 19);
    s12->setLink(1, *(gate.get()), 14);
    s13->setLink(1, *(gate.get()), 13);
    s14->setLink(1, *(gate.get()), 16);
    s15->setLink(1, *(gate.get()), 15);

    for (int i = 0; i < 16; i++) {
        a0->setValue(static_cast<nts::Tristate>(i % 2));
        a1->setValue(static_cast<nts::Tristate>(!(i % 4 || (i - 1) % 4)));
        a2->setValue(static_cast<nts::Tristate>(i >= 12 || (i >= 4 && i <= 7)));
        a3->setValue(static_cast<nts::Tristate>(i >= 8));
        nts::Tristate input1 = a0->compute();
        nts::Tristate input2 = a1->compute();
        nts::Tristate input3 = a2->compute();
        nts::Tristate input4 = a3->compute();

        cr_assert_eq(s0->compute(), !input1 && !input2 && !input3 && !input4);
        cr_assert_eq(s1->compute(), input1 && !input2 && !input3 && !input4);
        cr_assert_eq(s2->compute(), !input1 && input2 && !input3 && !input4);
        cr_assert_eq(s3->compute(), input1 && input2 && !input3 && !input4);
        cr_assert_eq(s4->compute(), !input1 && !input2 && input3 && !input4);
        cr_assert_eq(s5->compute(), input1 && !input2 && input3 && !input4);
        cr_assert_eq(s6->compute(), !input1 && input2 && input3 && !input4);
        cr_assert_eq(s7->compute(), input1 && input2 && input3 && !input4);
        cr_assert_eq(s8->compute(), !input1 && !input2 && !input3 && input4);
        cr_assert_eq(s9->compute(), input1 && !input2 && !input3 && input4);
        cr_assert_eq(s10->compute(), !input1 && input2 && !input3 && input4);
        cr_assert_eq(s11->compute(), input1 && input2 && !input3 && input4);
        cr_assert_eq(s12->compute(), !input1 && !input2 && input3 && input4);
        cr_assert_eq(s13->compute(), input1 && !input2 && input3 && input4);
        cr_assert_eq(s14->compute(), !input1 && input2 && input3 && input4);
        cr_assert_eq(s15->compute(), input1 && input2 && input3 && input4);
    }
    cr_assert_eq(gate->compute(0), 0);
}

/*
** CLOCK
*/

Test(Clock, test_clock, .init = redirect_all_std)
{
    std::unique_ptr<Clock> c = std::make_unique<Clock>("clock");

    c->dump();
    cr_assert_eq(c->getName(), "clock");
}

Test(Clock, test_clock2, .init = redirect_all_std)
{
    std::unique_ptr<Clock> c = std::make_unique<Clock>("clock");

    c->setValue(nts::FALSE);
    c->invertValue();
    cr_assert_eq(c->compute(), nts::TRUE);
}

Test(Clock, test_clock3, .init = redirect_all_std)
{
    std::unique_ptr<Clock> c = std::make_unique<Clock>("clock");

    c->setValue(nts::TRUE);
    c->invertValue();
    cr_assert_eq(c->compute(), nts::FALSE);
}

/*
** PARSER
*/

Test(Parser, test_parser, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/basic");
    char const *tab[] = {"./tests/basic", "a=1", "b=1", NULL};

    p->startParsing(tab);
    cr_assert_null(NULL);
}

Test(Parser, test_parser2, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/lot of c");
    char const *tab[] = {"./tests/lot of c", "a=1", "b=1", NULL};

    p->startParsing(tab);
    cr_assert_null(NULL);
}

Test(Parser, test_parser3, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error1");
    char const *tab[] = {"./tests/error1", "a=1", "b=1", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "component 'YES' doesn't exist");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser4, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error2");
    char const *tab[] = {"./tests/error2", "c=1", "b=1", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "a provided input 'c' is unknown");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser5, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error2");
    char const *tab[] = {"./tests/error2", "a=1", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "One or several input values are not provided");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser6, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error2");
    char const *tab[] = {"./tests/error2", "a=1", "csqdgqsd", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "One or several input values are not provided");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser7, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/not exist");
    char const *tab[] = {"./tests/not exist", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "file cannot be open");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser8, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error3");
    char const *tab[] = {"./tests/error3", NULL};
    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "no .chipsets section found");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser9, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error4");
    char const *tab[] = {"./tests/error4", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "component name 'truc' is unknown");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser10, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error5");
    char const *tab[] = {"./tests/error5", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "component name 'truc' is unknown");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser11, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error6");
    char const *tab[] = {"./tests/error6", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "no .links section found");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser12, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error7");
    char const *tab[] = {"./tests/error7", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "one or several chipsets contain a syntax error");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser13, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error8");
    char const *tab[] = {"./tests/error8", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "several components share the same name : prout");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser14, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error9");
    char const *tab[] = {"./tests/error9", NULL};

    try {
        p->startParsing(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "one or several links contain a syntax error");
        return;
    }
    cr_assert_not_null(NULL);
}

Test(Parser, test_parser15, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/error10");
    char const *tab[] = {"./tests/error10", "a=1", "b=1", NULL};

    p->startParsing(tab);
    p->changeClock();
    p->computeOutput();
    p->displayOutput();
    p->dump();
    cr_assert_null(NULL);
}

Test(Parser, test_parser16, .init = redirect_all_std)
{
    std::unique_ptr<Parser> p = std::make_unique<Parser>("./tests/lol");
    char const *tab[] = {"./tests/lol", "a=1", NULL};

    p->startParsing(tab);
    p->setInput("a", nts::UNDEFINED);
    p->computeOutput();
    p->displayOutput();
    cr_assert_null(NULL);
}

/*
** USER INPUT
*/

Test(UserInput, test_userinput, .init = redirect_all_std)
{
    char const *tab[] = {"./tests/basic", "a=1", "b=1", NULL};
    std::unique_ptr<UserInput> u = std::make_unique<UserInput>(tab);

    u->dump();
    u->display();
    u->displayPrompt();
    cr_assert_null(NULL);
}

Test(UserInput, test_userinput2, .init = redirect_all_std)
{
    char const *tab[] = {"./tests/basic", "a=1", "b=1", NULL};
    std::unique_ptr<UserInput> u = std::make_unique<UserInput>(tab);
    int status = 0;
    int fd[2];
    pid_t pid;

    pipe(fd);
    pid = fork();
    if (pid == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        u->run();
        exit(0);
    } else {
        sleep(1);
        close(fd[0]);
        write(fd[1], "a=0\n", 4);
        write(fd[1], "simulate\n", 9);
        write(fd[1], "display\n", 8);
        write(fd[1], "loop\n", 5);
        kill(pid, SIGINT);
        write(fd[1], "exit\n", 5);
        waitpid(pid, &status, 0);
        close(fd[1]);
    }
    u->computeInput("a=0");
    u->computeInput("simulate");
    u->computeInput("display");
    u->computeInput("exit");
    u->computeInput("dump");
    cr_assert_null(NULL);
}

Test(UserInput, test_userinput3, .init = redirect_all_std)
{
    char const *tab[] = {"./tests/basic", "a=1", "b=1", NULL};
    std::unique_ptr<UserInput> u = std::make_unique<UserInput>(tab);
    int fd[2];
    pid_t myPid = getpid();
    int status = 0;
    pid_t pid;

    pipe(fd);
    pid = fork();
    if (pid == 0) {
        sleep(1);
        close(fd[0]);
        write(fd[1], "loop\n", 5);
        sleep(1);
        kill(myPid, SIGINT);
        close(fd[1]);
        exit(0);
    } else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        u->run();
        waitpid(pid, &status, 0);
    }
    cr_assert_null(NULL);
}

Test(UserInput, test_userinput4, .init = redirect_all_std)
{
    char const *tab[] = {NULL};

    try {
        std::unique_ptr<UserInput> u = std::make_unique<UserInput>(tab);
    } catch (Errors const &e) {
        cr_assert_str_eq(e.what(), "file cannot be open");
        return;
    }
    cr_assert_not_null(NULL);
}
