def solve():
    # Read N, A, B
    try:
        N, A, B = map(int, input().split())
        S = input()
    except EOFError:
        return

    ans = 0

    # r_a: pointer for r_min(l)
    # r_b: pointer for r_max(l) - 1
    r_a = -1  # Represents (l-1)
    r_b = -1  # Represents (l-1)

    # Counts for the [l, r_a] interval
    count_a_ra = 0
    count_b_ra = 0

    # Counts for the [l, r_b] interval
    count_a_rb = 0
    count_b_rb = 0

    # l iterates from 0 to N-1
    for l in range(N):
        # --- [1] Remove S[l-1] from counts (when l > 0) ---
        if l > 0:
            if S[l - 1] == 'a':
                count_a_ra -= 1
                count_a_rb -= 1
            else:
                count_b_ra -= 1
                count_b_rb -= 1

        # --- [2] Adjust r_a and r_b if they are behind l ---
        # Ensure r_a >= l-1
        if r_a < l - 1:
            r_a = l - 1
            count_a_ra = 0
            count_b_ra = 0

        # Ensure r_b >= l-1
        if r_b < l - 1:
            r_b = l - 1
            count_a_rb = 0
            count_b_rb = 0

        # --- [3] Advance r_a to find r_min(l) ---
        # Find the smallest r_a such that count_a_ra >= A
        while r_a + 1 < N and count_a_ra < A:
            r_a += 1
            if S[r_a] == 'a':
                count_a_ra += 1
            else:
                count_b_ra += 1

        # --- [4] Advance r_b to find r_max(l)-1 ---
        # Find the largest r_b such that count_b_rb < B
        # Check S[r_b + 1] before adding it
        while r_b + 1 < N:
            next_b_count = count_b_rb
            if S[r_b + 1] == 'b':
                next_b_count += 1

            if next_b_count < B:
                r_b += 1
                if S[r_b] == 'a':
                    count_a_rb += 1
                else:
                    count_b_rb += 1
            else:
                break # S[r_b + 1] would violate count_b < B

        # --- [5] Calculate the number of valid r for this l ---

        # r_min_l: The smallest r (>= l)
        r_min_l = -1
        if count_a_ra < A:
            # We reached N-1 but 'a' count is still less than A
            r_min_l = N # Set to N (out of bounds)
        else:
            r_min_l = r_a # r_a is the first r that satisfies the 'a' condition

        # r_max_l_minus_1: The largest r (>= l)
        # r_b is already the largest r (<= N-1) that satisfies the 'b' condition
        r_max_l_minus_1 = r_b

        # The valid range for r is [r_min_l, r_max_l_minus_1]
        # Number of elements = r_max_l_minus_1 - r_min_l + 1
        num_valid_r = max(0, r_max_l_minus_1 - r_min_l + 1)

        ans += num_valid_r

    print(ans)

# Call the function to run
solve()
