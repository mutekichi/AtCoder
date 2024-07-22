package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	w := bufio.NewWriter(os.Stdout)
	defer w.Flush()

	var n int
	fmt.Fscan(r, &n)

	LR := make([][]int64, n)
	for i := 0; i < n; i++ {
		LR[i] = make([]int64, 2)
		fmt.Fscan(r, &LR[i][0], &LR[i][1])
		if LR[i][0] > LR[i][1] {
			LR[i][0], LR[i][1] = LR[i][1], LR[i][0]
		}
	}

	var sumMin, sumMax int64
	for i := 0; i < n; i++ {
		sumMin += LR[i][0]
		sumMax += LR[i][1]
	}

	ans := make([]int64, n)

	if sumMin <= 0 && 0 <= sumMax {
		fmt.Fprintln(w, "Yes")

		toAdded := -sumMin

		for i := 0; i < n; i++ {
			if toAdded > 0 {
				if toAdded >= LR[i][1]-LR[i][0] {
					toAdded -= LR[i][1] - LR[i][0]
					ans[i] = LR[i][1]
				} else {
					ans[i] = LR[i][0] + toAdded
					toAdded = 0
				}
			} else {
				ans[i] = LR[i][0]
			}
		}

		for i := 0; i < n; i++ {
			fmt.Fprint(w, ans[i])
			if i != n-1 {
				fmt.Fprint(w, " ")
			} else {
				fmt.Fprintln(w)
			}
		}
	} else {
		fmt.Fprintln(w, "No")
	}
}
