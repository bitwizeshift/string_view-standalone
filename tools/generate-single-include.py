#!/usr/bin/env python3
"""
generate-single-include.py

This stitches together the headers in this project into a single header.
It works by finding #include statements in the form of '#include "..."'
and extracting out the relative path from it, to stitch together headers.

This script will require tweaking to work with paths from a different base,
if the #include is not relative.
"""


def dump_contents(output, input_path):
  from pathlib import Path
  import re

  with open(input_path) as source:
    for line in source:
      line = line.rstrip()

      # This logic only works for relative headers using "" for search
      regex = '#include "(.*)"'
      if re.search(regex, line):
        path_segment = Path(re.sub(regex,'\\1',line))
        new_path = input_path.parent / path_segment

        dump_contents(output, new_path)
      else:
        output.write(f"{line}\n")


def main(argv):
  from pathlib import Path

  if len(argv) != 3:
    print("usage: {} <input file> <output file>".format(argv[0]))
    exit(1)

  input_name = Path(argv[1])
  output_name = Path(argv[2])

  with open(output_name, 'w') as dest:
    dump_contents(dest, input_name)

if __name__ == "__main__":
  import sys
  main(sys.argv)