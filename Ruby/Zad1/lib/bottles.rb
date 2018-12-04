class Bottles

   def drink_or_buy(bottles)
     if bottles > 0
       return "Take #{bottles == 1 ? 'it' : 'one'} down and pass it around"
     end
     return 'Go to the store and buy some more'
   end

   def drink_bottle(bottles)
     if bottles == 1
       return 'no more'
     elsif bottles == 0
       return 99
     else
       return bottles - 1
     end
   end

   def verse(page)
     return "#{page != 0 ? page : 'No more'} bottle#{'s' if page != 1} of beer on the wall, #{page != 0 ? page : 'no more'} bottle#{'s' if page != 1} of beer.
#{drink_or_buy(page)}, #{drink_bottle(page)} bottle#{'s' if page - 1 != 1} of beer on the wall.\n"
   end

   def verses(from_page, to_page=nil)
     if to_page == nil
       to_page = from_page
     end

     text_to_sing = ""
     for page in (to_page + 1..from_page).to_a.reverse do
       text_to_sing << verse(page) << "\n"
     end
     text_to_sing << verse(to_page)
     return text_to_sing
   end

   def song
    return verses(99, 0)
   end
end

puts Bottles.new.song
