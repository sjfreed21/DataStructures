% Samuel Freed
% Report Generator

data_A = csvread("../code/dataSetA.csv");
data_B = csvread("../code/dataSetB.csv");

LL_A = csvread("LL_insert_search_A.csv");
LL_B = csvread("LL_insert_search_B.csv");

BST_A = csvread("BST_insert_search_A.csv");
BST_B = csvread("BST_insert_search_B.csv");

Hash_A_Cha = csvread("Hash_insert_search_A_chain.csv");
Hash_A_Lin = csvread("Hash_insert_search_A_linear.csv");
Hash_A_Qua = csvread("Hash_insert_search_A_quad.csv");
Hash_B_Cha = csvread("Hash_insert_search_B_chain.csv");
Hash_B_Lin = csvread("Hash_insert_search_B_linear.csv");
Hash_B_Qua = csvread("Hash_insert_search_B_quad.csv");

%% Figure 1 - Data Sets
figure(1);
hold on
x = 1:40000;
scatter(x,data_A,0.5);
scatter(x,data_B,0.5);
title("Data Sets");
xlabel("Item");
ylabel("Value");
legend('Set A','Set B');
hold off

%% Figure 2 - Linked List A
figure(2);
hold on
i = 1:400;
plot(i,LL_A(1,1:400));
plot(i,LL_A(2,1:400));
title("Linked List A");
xlabel("Iteration");
ylabel("Average Time (ns)");
legend('Insert','Search');
hold off

%% Figure 3 - Linked List B
figure(3);
hold on
i = 1:400;
plot(i,LL_B(1,1:400));
plot(i,LL_B(2,1:400));
title("Linked List B");
xlabel("Iteration");
ylabel("Average Time (ns)");
legend('Insert','Search');
hold off

%% Figure 4 - BST A
figure(4);
hold on
i = 1:400;
plot(i,BST_A(1,1:400));
plot(i,BST_A(2,1:400));
title("BST A");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('Insert','Search');
hold off

%% Figure 5 - BST B
figure(5);
hold on
i = 1:400;
plot(i,BST_B(1,1:400));
plot(i,BST_B(2,1:400));
title("BST B");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('Insert','Search');
hold off

%% Figure 6 - Hash Chaining A
figure(6);
hold on
i = 1:400;
plot(i,Hash_A_Cha(1,1:400));
plot(i,Hash_A_Cha(2,1:400));
plot(i,Hash_A_Cha(3,1:400));
plot(i,Hash_A_Cha(4,1:400));
title("Hash Table Chaining A");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('Insert','Search','Insert Collisons','Search Collisions');
hold off

%% Figure 7 - Hash Chaining B
figure(7);
hold on
i = 1:400;
plot(i,Hash_B_Cha(1,1:400));
plot(i,Hash_B_Cha(2,1:400));
plot(i,Hash_B_Cha(3,1:400));
plot(i,Hash_B_Cha(4,1:400));
title("Hash Table Chaining B");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('Insert','Search','Insert Collisons','Search Collisions');
hold off

%% Figure 8 - Hash Linear A
figure(8);
hold on
i = 1:400;
plot(i,Hash_A_Lin(1,1:400));
plot(i,Hash_A_Lin(2,1:400));
plot(i,Hash_A_Lin(3,1:400));
plot(i,Hash_A_Lin(4,1:400));
title("Hash Table Linear A");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('Insert','Search','Insert Collisons','Search Collisions');
hold off

%% Figure 9 - Hash Linear B
figure(9);
hold on
i = 1:400;
plot(i,Hash_B_Lin(1,1:400));
plot(i,Hash_B_Lin(2,1:400));
plot(i,Hash_B_Lin(3,1:400));
plot(i,Hash_B_Lin(4,1:400));
title("Hash Table Linear B");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('Insert','Search','Insert Collisons','Search Collisions');
hold off

%% Figure 10 - Hash Quad A
figure(10);
hold on
i = 1:400;
plot(i,Hash_A_Qua(1,1:400));
plot(i,Hash_A_Qua(2,1:400));
plot(i,Hash_A_Qua(3,1:400));
plot(i,Hash_A_Qua(4,1:400));
title("Hash Table Quadratic A");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('Insert','Search','Insert Collisons','Search Collisions');
hold off

%% Figure 11 - Hash Quad B
figure(11);
hold on
i = 1:400;
plot(i,Hash_B_Qua(1,1:400));
plot(i,Hash_B_Qua(2,1:400));
plot(i,Hash_B_Qua(3,1:400));
plot(i,Hash_B_Qua(4,1:400));
title("Hash Table Quadratic B");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('Insert','Search','Insert Collisons','Search Collisions');
hold off

%% Figure 12 - Summary Inserts
figure(12);
i = 1:400;
subplot(2,1,1);
hold on
plot(i,LL_A(1,1:400));
plot(i,BST_A(1,1:400));
plot(i,Hash_A_Cha(1,1:400));
title("Best Inserts for A");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('LL','BST','Hash Chain');
subplot(2,1,2);
hold on
plot(i,LL_B(1,1:400));
plot(i,BST_B(1,1:400));
plot(i,Hash_B_Cha(1,1:400));
title("Best Inserts for B");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('LL','BST','Hash Chain');
hold off

%% Figure 13 - Summary Search
figure(13);
i = 1:400;
subplot(2,1,1);
hold on
plot(i,LL_A(2,1:400));
plot(i,BST_A(2,1:400));
plot(i,Hash_A_Cha(2,1:400));
title("Best Searches for A");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('LL','BST','Hash Chain');
subplot(2,1,2);
hold on
plot(i,LL_B(2,1:400));
plot(i,BST_B(2,1:400));
plot(i,Hash_B_Cha(2,1:400));
title("Best Searches for B");
xlabel("Iteration");
ylabel("Average Time (ns)");
ylim([0 1000]);
legend('LL','BST','Hash Chain');
