(0..100).each do |n|
  expression = (n & (n - 1) == 0)
  puts "#{n.to_s(2)}: #{expression}" if expression
end
