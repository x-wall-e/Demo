#include "common.h"


/**
  * @brief  Test to see if a key has been pressed on the HyperTerminal
  * @param  key: The key pressed
  * @retval 1: Correct
  *         0: Error
  */
uint32_t SerialKeyPressed(uint8_t *key)
{

	if ( USART_GetFlagStatus(EVAL_COM1, USART_FLAG_RXNE) != RESET)
	{
		*key = (uint8_t)EVAL_COM1->DR;
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief  Print a character on the HyperTerminal
  * @param  c: The character to be printed
  * @retval None
  */
void SerialPutChar(uint8_t c)
{
	USART_SendData(EVAL_COM1, c);
	//while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TXE) == RESET)
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{
	}
}

/**
  * @brief  Print a string on the HyperTerminal
  * @param  s: The string to be printed
  * @retval None
  */
void Serial_PutString(uint8_t *s)
{
#if (ENABLE_PUTSTR == 1)
	while (*s != '\0')
	{
		SerialPutChar(*s);
		s++;
	}
#endif
}

/**
  * @brief  Calculate the number of pages
  * @param  Size: The image size
  * @retval The number of pages
  */
uint32_t FLASH_PagesMask(__IO uint32_t Size)
{
	uint32_t pagenumber = 0x0;
	uint32_t size = Size;

	if ((size % PAGE_SIZE) != 0)
	{
		pagenumber = (size / PAGE_SIZE) + 1;
	}
	else
	{
		pagenumber = size / PAGE_SIZE;
	}
	return pagenumber;
}


uint8_t EraseSomePages(__IO uint32_t size, uint8_t outPutCont)
{
	uint32_t EraseCounter = 0x0;
	uint32_t NbrOfPage = 0;
	uint8_t erase_cont[3] = {0};
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	
	NbrOfPage = FLASH_PagesMask(size);

	/* Erase the FLASH pages */
	FLASH_Unlock();
	for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	{
		FLASHStatus = FLASH_ErasePage(ApplicationAddress + (PAGE_SIZE * EraseCounter));
		if(outPutCont == 1)
		{
			Int2Str(erase_cont, EraseCounter + 1);
			SerialPutString(erase_cont);
			SerialPutString("@");
		}
	}
	FLASH_Lock();
	if((EraseCounter != NbrOfPage) || (FLASHStatus != FLASH_COMPLETE))
	{
		return 0;
	}
	return 1;
}


/**
  * @brief  Get a key from the HyperTerminal
  * @param  None
  * @retval The Key Pressed
  */
uint8_t GetKey(void)
{
	uint8_t key = 0; 
  /* Waiting for user input */
	while (1)
	{
		if (SerialKeyPressed((uint8_t*)&key)) break;
	}
	return key;
}


/**
  * @brief  Convert an Integer to a string
  * @param  str: The string
  * @param  intnum: The intger to be converted
  * @retval None
  */
void Int2Str(uint8_t* str, int32_t intnum)
{
	uint32_t i, Div = 1000000000, j = 0, Status = 0;

	for (i = 0; i < 10; i++)
	{
		str[j++] = (intnum / Div) + 48;

		intnum = intnum % Div;
		Div /= 10;
		if ((str[j-1] == '0') & (Status == 0))
		{
			j = 0;
		}
		else
		{
			Status++;
		}
	}
}

/**
  * @brief  Convert a string to an integer
  * @param  inputstr: The string to be converted
  * @param  intnum: The intger value
  * @retval 1: Correct
  *         0: Error
  */
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
	uint32_t i = 0, res = 0;
	uint32_t val = 0;

	if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
	{
		if (inputstr[2] == '\0')
		{
			return 0;
		}
		for (i = 2; i < 11; i++)
		{
			if (inputstr[i] == '\0')
			{
				*intnum = val;
				/* return 1; */
				res = 1;
				break;
			}
			if (ISVALIDHEX(inputstr[i]))
			{
				val = (val << 4) + CONVERTHEX(inputstr[i]);
			}
			else
			{
				/* return 0, Invalid input */
				res = 0;
				break;
			}
		}
		/* over 8 digit hex --invalid */
		if (i >= 11)
		{
			res = 0;
		}
	}
	else /* max 10-digit decimal input */
	{
		for (i = 0;i < 11;i++)
		{
			if (inputstr[i] == '\0')
			{
				*intnum = val;
				/* return 1 */
				res = 1;
				break;
			}
			else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
			{
				val = val << 10;
				*intnum = val;
				res = 1;
				break;
			}
			else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
			{
				val = val << 20;
				*intnum = val;
				res = 1;
				break;
			}
			else if (ISVALIDDEC(inputstr[i]))
			{
				val = val * 10 + CONVERTDEC(inputstr[i]);
			}
			else
			{
				/* return 0, Invalid input */
				res = 0;
				break;
			}
		}
		/* Over 10 digit decimal --invalid */
		if (i >= 11)
		{
			res = 0;
		}
	}

	return res;
}
