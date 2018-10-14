int towerof_honai()
{
    int result;

    result = pop_stack1();
    push_stack2(result);
    result = pop_stack1();
    push_stack3(result);
    result = pop_stack2();
    push_stack3(result);
    result = pop_stack1();
    push_stack2(result);
    result = pop_stack3();
    push_stack2(result);
    result = pop_stack3();
    push_stack1(result);
    result = pop_stack2();
    push_stack1(result);
    result = pop_stack2();
    push_stack3(result);


    result = pop_stack1();
    push_stack2(result);
    result = pop_stack1();
    push_stack3(result);


    result = pop_stack2();
    push_stack3(result);
    display_stack3();
}
