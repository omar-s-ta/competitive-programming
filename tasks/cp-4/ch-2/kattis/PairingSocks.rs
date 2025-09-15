use std::io::{self, prelude::*};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let _n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    let socks: Vec<i32> = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut socks = socks;
    socks.reverse();

    let mut stk = Vec::new();
    let mut aux_stk = Vec::new();

    for sock in socks {
        stk.push(sock);
    }

    let mut result = 0;
    while let Some(ai) = stk.pop() {
        if let Some(&aai) = aux_stk.last() {
            if ai == aai {
                aux_stk.pop();
            } else {
                aux_stk.push(ai);
            }
        } else {
            aux_stk.push(ai);
        }
        result += 1;
    }

    if aux_stk.is_empty() {
        println!("{}", result);
    } else {
        println!("impossible");
    }
}
