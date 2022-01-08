/*
Arduino Template Library https://github.com/obiwanjacobi/atl
Written by Marc Jacobi
Copyright 2012-2015 All Rights Reserved

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "TextFormatInfo.h"

namespace ATL {
	
char TextFormatInfo::NewLine[] = { '\r', '\n', '\0' };
uint8_t TextFormatInfo::DecimalDigits = (uint8_t )2;
char TextFormatInfo::NegativeSign = { '-' };
char TextFormatInfo::DecimalSeparator = { '.' } ;
uint8_t TextFormatInfo::DefaultBase = (uint8_t )TextFormatInfo::baseDecimal;

} // AT:L