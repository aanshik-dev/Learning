int _print_t(nptr root, int is_left, int offset, int depth, int dep, char s[dep][255]) {
   char b[15];
   int width = 5;

   if (!root)
      return 0;

   sprintf(b, "(%03d)", root->data);

   int left = _print_t(root->left, 1, offset, depth + 1, dep, s);
   int right = _print_t(root->right, 0, offset + left + width, depth + 1, dep, s);

#ifdef COMPACT
   for (int i = 0; i < width; i++)
      s[depth][offset + left + i] = b[i];

   if (depth && is_left) {

      for (int i = 0; i < width + right; i++)
         s[depth - 1][offset + left + width / 2 + i] = '-';

      s[depth - 1][offset + left + width / 2] = '.';

   } else if (depth && !is_left) {

      for (int i = 0; i < left + width; i++)
         s[depth - 1][offset - width / 2 + i] = '-';

      s[depth - 1][offset + left + width / 2] = '.';
   }
#else
   for (int i = 0; i < width; i++)
      s[2 * depth][offset + left + i] = b[i];

   if (depth && is_left) {
      for (int i = 0; i < width + right; i++)
         s[2 * depth - 1][offset + left + width / 2 + i] = '-';

      s[2 * depth - 1][offset + left + width / 2] = '+';
      s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

   } else if (depth && !is_left) {

      for (int i = 0; i < left + width; i++)
         s[2 * depth - 1][offset - width / 2 + i] = '-';

      s[2 * depth - 1][offset + left + width / 2] = '+';
      s[2 * depth - 1][offset - width / 2 - 1] = '+';
   }
#endif

   return left + width + right;
}

void print_tree(nptr tree, int dep) {
   char s[dep][255];
   for (int i = 0; i < dep; i++)
      sprintf(s[i], "%80s", " ");

   _print_t(tree, 0, 0, 0, dep, s);

   for (int i = 0; i < dep; i++)
      printf("%s\n", s[i]);
}