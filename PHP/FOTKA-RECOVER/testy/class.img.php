<?php
/**
*	class Image
*
*	utworzenie obiektu klasy Image
*	$img = new Image(string ŚcieżkaDoPliku);								// grafika typu: GIF, JPG lub PNG
*
*	$img->SetWidth(int NowaSzerokość [, bool ZachowajProporcje = true]);	// zmiana szerokości grafiki
*	$img->SetHeight(int NowaWysokość [, bool ZachowajProporcje = true]);	// zmiana wysokości grafiki
*	$img->SetSize(int NowaSzerokość ,int NowaWysokość);						// zmiana wymiarów (szerokości i wysokości) grafiki
*	$img->SetMaxSize(int MaksymalnyWymiar);									// ustawienie dłuższego boku grafiki
*	$img->Save(string NazwaPliku)											// zapis grafiki do pliku
*	$img->Send()															// wysłanie grafiki do przeglądarki
*/

class Image
{	private $_img;				// uchwyt (handler) grafiki
	private $_src_file;			// plik z grafiką
	private $_img_info;			// tablica  z getmageinfo()

	private $_dest_type = "jpg";				// typ grafiki
	private $_dest_width = 0;					// szerokość wynikowa grafiki
	private $_dest_height = 0;					// wysokość wynikowa grafiki

	/**
	 * Konstruktor klasy
	 * @paramertr string	$sFileName - plik z grafiką
	 * @return void
	 */
	public function __construct($sFileName) 
	{	$this->_img_info = @getimagesize($sFileName);
		if (!is_array($this->_img_info))		return false;
		// $_img_info[2]: 1 = GIF, 2 = JPG, 3 = PNG
		switch ($this->_img_info[2])
		{	case 1:		$this->_img = @ImageCreateFromGIF($sFileName);		break;
			case 2:		$this->_img = @ImageCreateFromJPEG($sFileName);		break;
			case 3:		$this->_img = @ImageCreateFromPNG($sFileName);		break;
			default:	return false;
		}
		return $this->_img;
	}

	/**
	 * Metoda definiująca typ grafiki wynikowej
	 * @paramertr string $sDestType - typ grafiki
	 * @return void
	 */
	public function SetType($sDestType)
	{	$sDestType = strtolower($sDestType);
		if ($sDestType == "gif" || $sDestType == "png" || $sDestType == "jpg")
				$this->_dest_type = $sDestType;
	}

	/**
	 * Metoda definiująca szerokość grafiki
	 * @paramertr int	$iNewWidth - nowa szerokość
	 * @paramertr bool	$bProportional - zachowaj proporcje
	 * @return void
	 */
	public function SetWidth($iNewWidth, $bProportional = 1)
	{	$this->_dest_width = $iNewWidth;
		if ($bProportional)
		{	$this->_dest_height = intval($this->_img_info[1] * ($iNewWidth / $this->_img_info[0]));
		}
	}
	
	/**
	 * Metoda definiująca wysokość grafiki
	 * @paramertr int	$iNewHeight - nowa wysokość
	 * @paramertr bool	$bProportional - zachowaj proporcje
	 * @return void
	 */
	public function SetHeight($iNewHeight, $bProportional = 1)
	{	$this->_dest_height = $iNewHeight;
		if ($bProportional)
		{	$this->_dest_width = intval($this->_img_info[0] * ($iNewHeight / $this->_img_info[1]));
		}
	}
	
	/**
	 * Metoda definiująca szerokość i wysokość grafiki
	 * @paramertr int	$iNewWidth - szerokość
	 * @paramertr int	$iNewHeight - wysokość
	 * @return void
	 */
	function SetSize($iNewWidth, $iNewHeight)
	{	$this->_dest_width = $iNewWidth;
		$this->_dest_height = $iNewHeight;
	}

	/**
	 * Metoda skalująca grafikę
	 * @paramertr int	$iMaxSize - maksymalny wymiar (szerokość lub wysokość)
	 * @return void
	 */
	public function SetMaxSize($iMaxSize)
	{	if (!is_int($iMaxSize))		return false;
		if ($iMaxSize <= 0)			return false;
		if($this->_img_info[0] <= $iMaxSize && $this->_img_info[1] <= $iMaxSize)		return true;
		if($this->_img_info[0] > $this->_img_info[1])		//szerszy ni wyszy
		{	$this->_dest_width = $iMaxSize;
			$this->_dest_height = intval($this->_img_info[1] * ($iMaxSize / $this->_img_info[0]));
		}
		else		//wyszy niz szerszy
		{	$this->_dest_height = $iMaxSize;
			$this->_dest_width = intval($this->_img_info[0] * ($iMaxSize / $this->_img_info[1]));
		}
	}

	/**
	 * Zapis do pliku
	 * @paramertr string	$sFileName - ścieżka do pliku
	 * @return void
	 */
	public function Save($sFileName)
	{	if (!is_string($sFileName))			return false;

		if($this->_dest_width == 0 )		$this->_dest_width = $this->_img_info[0];
		if($this->_dest_height == 0 )		$this->_dest_height = $this->_img_info[1];

		$img_new = ImageCreateTrueColor($this->_dest_width, $this->_dest_height);
		ImageCopyResampled($img_new, $this->_img, 0, 0, 0, 0, $this->_dest_width, $this->_dest_height, $this->_img_info[0], $this->_img_info[1]);

		if ($this->_dest_type == "jpg" || $this->_dest_type == "jpeg")	@ImageJPEG($img_new, $sFileName);
		elseif ($this->_dest_type == "gif")								@ImageGIF($img_new, $sFileName);
		else															@ImagePNG($img_new, $sFileName);
	}
	

	/**
	 * Wysłanie do przeglądarki
	 * @paramertr void
	 * @return void
	 */
	public function Send()
	{	if($this->_dest_width == 0 )		$this->_dest_width = $this->_img_info[0];
		if($this->_dest_height == 0 )		$this->_dest_height = $this->_img_info[1];
		
		$img_new = ImageCreateTrueColor($this->_dest_width, $this->_dest_height);
		ImageCopyResampled($img_new, $this->_img, 0, 0, 0, 0, $this->_dest_width, $this->_dest_height, $this->_img_info[0], $this->_img_info[1]);

		$this->_dest_type = ($this->_dest_type=="jpg") ? "jpeg" : $this->_dest_type;
		$fun = "image".$this->_dest_type;
		
		header('Content-type: '.$this->_img_info["mime"]);
		$fun($img_new);
        imagedestroy($this->img);
        return;
	}

	/**
	 * Pobierz typ grafiki
	 * @paramertr void
	 * @return string - typ grafiki mime
	 */
	public function GetImgType()
	{	return $this->_img_info["mime"];
	}

	/**
	 * Pobierz szerokość grafiki
	 * @paramertr void
	 * @return int - szerokość grafiki
	 */
	public function GetImgWidth()
	{	return $this->_dest_width;
	}

	/**
	 * Pobierz wysokość grafiki
	 * @paramertr void
	 * @return int - wysokość grafiki
	 */
	public function GetImgHeight()
	{	return $this->_dest_height;
	}

	/**
	 * Pobierz atrybuty HEIGHT i WIDTH dla tagu <IMG>
	 * @paramertr void
	 * @return string - atrybuty <IMG>
	 */
	public function GetImgHTML()
	{	return $this->_img_info[3];
	}

	/**
	 * Destruktor klasy
	 * @paramertr void
	 * @return void
	 */
	public function __destruct()
	{	imagedestroy($this->_img);
	}
}//koniec klasy
?>
