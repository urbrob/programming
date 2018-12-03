class Bottles

   def drink_or_buy(bootles)
     if bottles > 0
       return 'Take it down and pass it around'
     return 'Go to the store and buy some more'
   end

   def sing_page(page)
     <<-EOF
          #{page != 0 ? page : 'No more'} bottles of beer on the wall, #{page != 0 ? page : 'no more'} of beer.
          #{drink_or_buy(page)}, #{page != 0 ? page : 'no more'} of beer on the wall.
        EOF
   end

   def verse(from_page, to_page=from_page)
     for page in from_page..to_page do
       sing_page(page)
     end
   end

   def song
    verse(99, 0)
   end
end
