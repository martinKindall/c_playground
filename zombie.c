int main() {
  int a = 2;
  if (fork() == 0)
    sleep(10);
  return 0;
}
