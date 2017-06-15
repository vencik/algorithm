match() {
    cmd="$1"
    in="$2"
    x_out="$3"

    in_file=$(mktemp --tmpdir=${PWD} input.XXXXXXXXXX)
    x_out_file=$(mktemp --tmpdir=${PWD} expected_output.XXXXXXXXXX)
    out_file=$(mktemp --tmpdir=${PWD} output.XXXXXXXXXX)

    echo "$in" > "$in_file"
    echo "$x_out" > "$x_out_file"

    cat "$in_file" | eval "$cmd" > "$out_file"

    if ! diff "$out_file" "$x_out_file"; then
        cat >&2 <<HERE
Command
$cmd
output in
$out_file
doesn't match expected output in
$x_out_file
The input is in
$in_file
HERE

        return 1
    fi

    rm "$in_file" "$x_out_file" "$out_file"
}
