/*-----------------sastantua.c-------------------*/

#include "sastantua_h.h"

int	edge_len(int height)
{
  /* с 4 по 9 уровень - выступ уровня 4 звезды */
  if (height > 3)
    return (4);
  /* c 2 по 3 уровень - выступ уровня 3 звезды */
  if (height > 1)
    return (3);
  /* первый уровень выступа не имеет */
  return (0);
}

int	gate_size(int height)
{
  /* если высота пирамиды от 5 до 9, то считаем ширину*/
  if (height > 4)
    {
      /* если высота нечетная, то ширина ворот подходит */
      if (height % 2)
	return (height);
      else
	/* иначе размер сохраняется как на предыдущем*/
	return (height - 1);
    }
  /* если высота пирамиды от 2 до 4, ширина ворот равна 3*/
  if (height > 1)
    return (3);
  /* если высота 1, то ширина ворот 1 */
  return (1);
}

int	build_gate(int idx, int gsize, int line)
{
  int i;

  i = gsize;
  while (i-- > 0)
    {
      /* если размер ворот больше 5
      ** отрисовывается середина ворот: нужна линия - 1, 
      ** т.к. нумерация линий сверху вниз от высоты пирамиды
      ** отрисовывется предпоследний элемент
      ** то ставим ручку */
      if (gsize > 4 && line - 1 == (gsize / 2) && i == 1)
	ft_putchar('$');
      else
	ft_putchar('|');
      idx++;
    }
  return (idx);
}

int	build_block(int hgt, int prev_els, int last, int shift)
{
  int lines;
  int cur_els;
  int idx;

  /* число элементов в начале блока = число эл-тов пред. блока + (грань текущего блока * 2) */
  cur_els = prev_els + (edge_len(hgt) * 2);
  /* число линий в блоке = текущий уровень + 2 */
  lines = hgt + 2;
  while (lines > 0)
    {
      idx = shift--;
      while (idx-- > 0)
	  ft_putchar(' ');
      ft_putchar('/');
      idx = 0;
      while (idx++ < cur_els)
	{
	  /* ворота строятся в посленем блоке
	  ** высота ворот должна совпадать с высотой пирамиды 
	  ** ворота отрисовываются по центру строки */
	  if (last && lines <= hgt && (idx - 1) == (cur_els - gate_size(hgt)) / 2)
	    idx = build_gate(idx, gate_size(hgt), lines);
	  ft_putchar('*');
	}
      ft_putchar('\\');
      ft_putchar('\n');
      lines--;
      /* на следующей линии с каждой стороны добавляется по звезде */
      cur_els += 2;
      /* уменьшаем смещение на единицу */
    }
  /* уменьшаем на 2 звезды, т.к. нет захода в новый цикл */
  return (cur_els - 2);
}

void	sastantua(int size)
{
  int hgt;
  int lblock;
  int prev_els;
  int shift;
  
  hgt = 1; /* пирамида содержит хотя бы 1 блок */
  shift = 1;
  lblock = 0;
  prev_els = 1; //в вершине одна звезда
  /* расчет отступов
   * отступы делаются для печати вершины пирамиды по центру */
  while (hgt <= size)
    {
      /* число элементов в основании текущего уровня 
       * = число элементов в основании предыдущего уровня + 
       * + (длина выступа след.уровней * 2) + число строк текущего уровня * 2
       *  число строк текущего уровня = номер уровня + 1 
       * т.к. например на 2 уровне 4 строки, но первую не учитываем, остается 3 */
      shift = shift + (edge_len(hgt) * 2) + ((hgt + 1) * 2);
      hgt++;
    }
  hgt = 1;
  /* кол-во отсутпов до середины = длина основания / 2 */
  shift /= 2;
  while (hgt <= size)
    {
      /* идентификация последнего блока для отрисовки ворот */
      if (hgt == size)
	lblock = 1;
      prev_els = build_block(hgt, prev_els, lblock, shift);
      /* уменьшаем отступ = текущий отступ - номер след уровня + грань след. уровня */
      hgt++;
      shift -= hgt + edge_len(hgt);
    }
}
