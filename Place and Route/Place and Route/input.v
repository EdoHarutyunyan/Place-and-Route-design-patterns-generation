module c17 (N1, N2, N3, N6, N7, N22, N23);

input N1, N2, N3, N6, N7;

output N22, N23;

wire N10, N11, N16, N19, N20;

nand NAND (N10, N1, N3);
and AND (N11, N3, N6);
or OR (N16, N2, N11);
nor NOR (N19, N11, N7);
not NOT (N20, N19);
xor XOR (N22, N10, N16);
xnor XNOR (N23, N16, N20);

endmodule