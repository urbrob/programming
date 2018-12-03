class Bottles

   def drink_or_buy(bottles)
     if bottles > 0
       return "Take #{bottles == 1 ? 'it' : 'one'} down and pass it around"
     return 'Go to the store and buy some more'
    end
   end

   def verse(page)
     return "#{page != 0 ? page : 'No more'} bottles of beer on the wall, #{page != 0 ? page : 'no more'} bottles of beer.
#{drink_or_buy(page)}, #{page != 1 ? page - 1 : 'no more'} bottles of beer on the wall.\n"
   end

   def verses(from_page, to_page=from_page)
     text_to_sing = ''
     for page in from_page..to_page do
       text_to_sing << verse(page)
     end
     return text_to_sing
   end

   def song
    return verse(99, 0)
   end
end
