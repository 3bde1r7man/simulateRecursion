#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>

using namespace std;

int F(int n) //recursion function
{
    if (n <= 1)
        return 1;
    int a = n * F(n - 1) + 7 * F(n / 2);
    int b = F(n - 3 - a % 2);
    return a + b;
}


struct Call
{
    int n; // parameter
    int a, b, c; // local variables
    int cur_loc; // location of next statement to be executed
};

int G(int n) // Non−recursive version of F()
{
    Call initial_call;
    initial_call.n = n;
    initial_call.cur_loc = 0;
    stack<Call> st;
    st.push(initial_call);
    int last_ret_val = 0; // Return value of last finished call

    while (!st.empty())
    {
        Call& call = st.top();
        if (call.cur_loc == 0)
        {
            if (call.n <= 1)
            {
                // Call finished, save return value and pop stack
                last_ret_val = 1;
                st.pop();
            }
            else
            {
                // Make new child call F(n−1) and push to stack
                Call new_call;
                new_call.cur_loc = 0;
                new_call.n = call.n - 1;
                st.push(new_call);
                // Update current location inside parent call
                call.cur_loc = 1;
            }
        }
        else if (call.cur_loc == 1)
        {
            //  a = n * F(n-1)
            call.a = call.n * last_ret_val;

            // Make new child call F(n/2) and push to onto stack
            Call new_call;
            new_call.cur_loc = 0;
            new_call.n = call.n / 2;
            st.push(new_call);
            // Update current location inside parent call
            call.cur_loc = 2;
        }
        else if (call.cur_loc == 2)
        {
            // c = 7 * F(n/2)
            call.c = 7 * last_ret_val;

            // Make new child call F(n-3-a%2) and push to onto stack
            Call new_call;
            new_call.cur_loc = 0;
            new_call.n = call.n - 3 - ((call.a + call.c) % 2);
            st.push(new_call);
            // Update current location inside parent call
            call.cur_loc = 3;

        }
        else if (call.cur_loc == 3)
        {
            // b = F(n-3-a%2)
            call.b = last_ret_val;
            // Call finished, save return value and pop stack
            // the final result a + b + c
            last_ret_val = call.a + call.c + call.b;
            st.pop();
        }
    }


    return last_ret_val;
}



int main()
{
    int n ;
    for (n = 1; n <= 20; n++)
    {
        cout << "G(" << n << ") = " << G(n) << endl;
        cout << "F(" << n << ") = " << F(n) << endl<<endl;
    }

    return 0;
}
