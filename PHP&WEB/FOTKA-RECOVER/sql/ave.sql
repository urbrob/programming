-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Czas generowania: 03 Lut 2017, 23:43
-- Wersja serwera: 10.1.16-MariaDB
-- Wersja PHP: 5.6.24

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Baza danych: `ave`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `albumy`
--

CREATE TABLE `albumy` (
  `id` int(11) NOT NULL,
  `tytul` varchar(100) COLLATE utf8_polish_ci NOT NULL,
  `data` date NOT NULL,
  `id_uzytkownika` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `uzytkownicy`
--

CREATE TABLE `uzytkownicy` (
  `id` int(11) NOT NULL,
  `login` varchar(20) COLLATE utf8_polish_ci NOT NULL,
  `hasło` varchar(32) COLLATE utf8_polish_ci NOT NULL,
  `email` varchar(128) COLLATE utf8_polish_ci NOT NULL,
  `zarejestrowany` date NOT NULL,
  `uprawnienia` enum('uzytkownik','moderator','administrator') COLLATE utf8_polish_ci NOT NULL,
  `aktywny` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `uzytkownicy`
--

INSERT INTO `uzytkownicy` (`id`, `login`, `hasło`, `email`, `zarejestrowany`, `uprawnienia`, `aktywny`) VALUES
(1, 'robcio', '883ab664180407bda9659d1ba774802c', 'cadad@o2.pl', '2016-12-22', 'administrator', 1),
(2, 'robercik', '14b0e4f335a105a131545bf3fa2683ba', 'awdawdaw@o2.pl', '2017-02-02', 'administrator', 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `zadjecia`
--

CREATE TABLE `zadjecia` (
  `id` int(11) NOT NULL,
  `tytul` varchar(255) COLLATE utf8_polish_ci NOT NULL,
  `id_albumu` int(11) NOT NULL,
  `data` date NOT NULL,
  `id_uzytkownika` int(11) NOT NULL,
  `zaakceptowane` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `zadjecia_komentarze`
--

CREATE TABLE `zadjecia_komentarze` (
  `ID` int(11) NOT NULL,
  `id_zdjecia` int(11) NOT NULL,
  `id_uzytkownika` int(11) NOT NULL,
  `data` date NOT NULL,
  `komentarz` varchar(11) COLLATE utf8_polish_ci NOT NULL,
  `zaakceptowany` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `zadjecia_oceny`
--

CREATE TABLE `zadjecia_oceny` (
  `id_zdjecia` int(11) NOT NULL,
  `id_uzytkownika` int(11) NOT NULL,
  `ocena` tinyint(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Indeksy dla zrzutów tabel
--

--
-- Indexes for table `albumy`
--
ALTER TABLE `albumy`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `uzytkownicy`
--
ALTER TABLE `uzytkownicy`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `zadjecia`
--
ALTER TABLE `zadjecia`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `zadjecia_komentarze`
--
ALTER TABLE `zadjecia_komentarze`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT dla tabeli `albumy`
--
ALTER TABLE `albumy`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT dla tabeli `uzytkownicy`
--
ALTER TABLE `uzytkownicy`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT dla tabeli `zadjecia`
--
ALTER TABLE `zadjecia`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
--
-- AUTO_INCREMENT dla tabeli `zadjecia_komentarze`
--
ALTER TABLE `zadjecia_komentarze`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
